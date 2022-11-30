#include "GameObj.h"

GameObj::GameObj(int starNumber)
	: destination(0, 0), move(false), attack(false), isAlive(true),
	currState(AnimStates::None), attackRangeType(false), isBattle(false),
	noSkill(false), ccTimer(0.f), shieldAmount(0.f), astarDelay(0.0f)
{
	hpBar = new TwoFactorProgress(TILE_SIZE * 0.8f, 5.f);
	hpBar->SetProgressColor(Color::Green);
	hpBar->SetBackgroundColor(Color(0, 0, 0, 100));
	hpBar->SetBackgroundOutline(Color::Black, 2.f);
	hpBar->SetSecondProgressColor(Color::White);

	star = new Star(starNumber);
}

GameObj::~GameObj()
{
}

void GameObj::Init()
{
	Vector2f hitboxSize(
		GetTextureRect().width * 0.5f < TILE_SIZE ? TILE_SIZE : GetTextureRect().width * 0.5f,
		GetTextureRect().height * 0.5f < TILE_SIZE ? TILE_SIZE : GetTextureRect().height * 0.5f);
	
	SetHitbox(FloatRect(0, 0, hitboxSize.x, hitboxSize.y), Origins::BC);
	UpgradeCharacterSet();
	Object::Init();

	SetStatsInit(GAME_MGR->GetCharacterData(name));

	hpBarLocalPos = { -hpBar->GetSize().x * 0.5f, -(float)GetTextureRect().height + 20.f };
	SetHpBarValue(1.f);
	hpBar->SetOrigin(Origins::BC);
	starLocalPos = { 0.f, hpBarLocalPos.y };
	SetPos(position);

	//battle
	enemyInfo.leng = 99999;

	if (!type.compare("Player"))
		targetType = "Monster";
	else if (!type.compare("Monster"))
		targetType = "Player";
	else
		targetType = "None";

	m_floodFill.SetArrSize(
		stat[Stats::AR].GetModifier(),
		stat[Stats::AR].GetModifier(),
		attackRangeType);

	m_attackDelay = 0.f;
}

void GameObj::Reset()
{
	isBattle = false;
	attack = false;
	move = false;
	isAlive = true;
	SetState(AnimStates::Idle);
}

void GameObj::Update(float dt)
{
	hpBar->Update(dt);
	// Dev key start
	{
		if (InputMgr::GetKeyDown(Keyboard::Key::S))
		{
			TakeCare(this, false);
			hpBar->SetRatio(stat[Stats::HP].GetModifier(), stat[Stats::HP].current, shieldAmount);
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::A))
		{
			TakeDamage(this);
			hpBar->SetRatio(stat[Stats::HP].GetModifier(), stat[Stats::HP].current, shieldAmount);
		}

		if (InputMgr::GetKeyDown(Keyboard::Key::D))
		{
			TakeCare(this);
			hpBar->SetRatio(stat[Stats::HP].GetModifier(), stat[Stats::HP].current, shieldAmount);
		}
	}
	// Dev key end

	if (isBattle)
	{
		if (!move && !attack && isAttack())
		{
			if (m_attackDelay <= 0.f)
			{
				SetState(AnimStates::Attack);
				attack = true;
				Stat& mp = stat[Stats::MP];
				mp.TranslateCurrent(15.f);
				if (Utils::EqualFloat(mp.GetCurRatio(), 1.f))
				{
					cout << name << " fire skill !" << endl;
					mp.SetCurrent(0.f);
				}
			}
			m_attackDelay -= dt;
		}
		else if (!move && !attack)
		{
			astarDelay -= dt;
			if (astarDelay <= 0.f)
			{
				destination = GetPos();
				if (SetTargetDistance())
				{
					move = true;
				}
				else
				{
					move = false;
					astarDelay = 0.1f;
				}
			}
		}

		if (move && !attack)
		{
			SetState(AnimStates::Move);
			direction = destination - position;
			Translate(Utils::Normalize(direction) * 0.5f);
			if (destination == position)
			{
				move = false;
				SetState(AnimStates::MoveToIdle);
			}
		}
	}
}

void GameObj::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(attackSprite);
	hpBar->Draw(window);
	star->Draw(window);
}

void GameObj::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	attackSprite.setPosition(GetPos());
	hpBar->SetPos(pos + hpBarLocalPos);
	star->SetPos(pos + starLocalPos);
}

void GameObj::SetState(AnimStates newState)
{
	IsSetState(newState);

	if (currState == newState)
	{
		return;
	}

	currState = newState;

}

void GameObj::SetStatsInit(json data)
{
	stat.insert({ Stats::HP, Stat(data["HP"]) });
	stat.insert({ Stats::MP, Stat(data["MP"], 0.f, false) });
	stat.insert({ Stats::AD, Stat(data["AD"]) });
	stat.insert({ Stats::AP, Stat(data["AP"]) });
	stat.insert({ Stats::AS, Stat(data["AS"]) });
	stat.insert({ Stats::AR, Stat(data["AR"]) });
	stat.insert({ Stats::MS, Stat(data["MS"]) });
	string arType = data["ARTYPE"];
	attackRangeType = arType.compare("cross") ? true : false;
}

void GameObj::TakeDamage(GameObj* attacker, bool attackType)
{
	Stat& hp = stat[Stats::HP];
	float damage = 0.f;
	if (attackType)
		damage = attacker->GetStat(Stats::AD).GetModifier();
	else
		damage = attacker->GetStat(Stats::AP).GetModifier();

	if (shieldAmount > 0.f)
	{
		float damageTemp = damage;
		damage -= shieldAmount;
		shieldAmount -= damageTemp;

		if (shieldAmount < 0.f)
			shieldAmount = 0.f;
		if (damage < 0.f)
			damage = 0.f;
	}

	hp.TranslateCurrent(-damage);
	hpBar->SetRatio(stat[Stats::HP].GetModifier(), stat[Stats::HP].current, shieldAmount);
	if (stat[Stats::HP].GetCurrent() <= 0.f)
	{
		// death
		CLOG::Print3String(name, to_string(GetStarNumber()), " is die");
	}
}

void GameObj::TakeCare(GameObj* caster, bool careType)
{
	Stat& hp = stat[Stats::HP];
	float careAmount = caster->GetStat(Stats::AP).GetModifier();

	if (careType)
		hp.TranslateCurrent(careAmount);
	else
		shieldAmount += careAmount;

	hpBar->SetRatio(stat[Stats::HP].GetModifier(), stat[Stats::HP].current, shieldAmount);
}

void GameObj::UpgradeStar()
{
	if (star->CalculateRandomChance())
		CLOG::Print3String("upgrade 2");
	star->UpdateTexture();
	UpgradeCharacterSet();

	m_attackDelay = 1.f / stat[Stats::AS].GetModifier();
}

void GameObj::UpgradeCharacterSet()
{
	sprite.setScale({
		1.0f + (GetStarNumber() * 0.05f),
		1.0f + (GetStarNumber() * 0.05f) });
}

void GameObj::IsSetState(AnimStates newState)
{
	if (newState != AnimStates::Attack && currState == AnimStates::Attack)
	{
		attack = false;
		m_attackDelay = 1.f / stat[Stats::AS].GetModifier();
	}
}

void GameObj::PrintStats()
{
	cout << "---------------" << endl;
	cout << "name: " << name << " / star: " << GetStarNumber() << endl;
	cout << "HP: " << stat[Stats::HP].GetBase() << endl;
	cout << "MP: " << stat[Stats::MP].GetBase() << endl;
	cout << "AD: " << stat[Stats::AD].GetBase() << endl;
	cout << "AP: " << stat[Stats::AP].GetBase() << endl;
	cout << "AS: " << stat[Stats::AS].GetBase() << endl;
	cout << "AR: " << stat[Stats::AR].GetBase() << endl;
	cout << "MS: " << stat[Stats::MS].GetBase() << endl;
	cout << (attackRangeType ? "square" : "cross") << endl;
	cout << "---------------" << endl;
}

unordered_map<Stats, Stat>& GameObj::GetStat()
{
	return stat;
}

bool GameObj::isAttack()
{
	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	for (auto& target : mainGrid)
	{
		if (target != nullptr && !target->GetType().compare(targetType))
		{
			Vector2i mypos = GAME_MGR->PosToIdx(GetPos());
			Vector2i enpos = GAME_MGR->PosToIdx(target->GetPos());

			if (m_floodFill.FloodFillSearch(mainGrid, mypos, enpos, targetType))
				return true;
		}
	}

	return false;
}

void GameObj::PlayAstar()
{

}

bool GameObj::SetTargetDistance()
{
	//move = true;

	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	for (auto& target : mainGrid)
	{
		if (target != nullptr && !target->GetType().compare(targetType))
		{
			Vector2i mypos = GAME_MGR->PosToIdx(GetPos());
			Vector2i enpos = GAME_MGR->PosToIdx(target->GetPos());
			EnemyInfo nowEnemyInfo = m_aStar.AstarSearch(mainGrid, mypos, enpos);

			if (enemyInfo.leng > nowEnemyInfo.leng && !(nowEnemyInfo.leng == -1))
			{
				enemyInfo = nowEnemyInfo;
			}
		}
	}

	if (enemyInfo.leng == 99999)
	{
		return false;
	}

	Vector2i coord = GAME_MGR->PosToIdx(GetPos());
	SetDestination(GAME_MGR->IdxToPos(enemyInfo.destPos));
	SetMainGrid(coord.y, coord.x, nullptr);
	SetMainGrid(enemyInfo.destPos.y, enemyInfo.destPos.x, this);
	enemyInfo.leng = 99999;
	return true;
}

void GameObj::SetMainGrid(int r, int c, GameObj* character)
{
	vector<GameObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	int idx = r * GAME_TILE_WIDTH + c;
	mainGrid[idx] = character;
}