#include "DanielSkill.h"
#include "Character.h"

DanielSkill::DanielSkill(int starNumber)
	: Skill(starNumber)
{
	baseDamage = { 50, 60, 70, 80 };
	range.resize(TIER_MAX);

	// cross 3x3
	range[0] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
	// square 3x3
	range[1] = { {1, -1}, {-1, -1}, {-1, 1}, {1, 1} };
	// cross 5x5
	range[2] = { {0, -2}, {0, 2}, {-2, 0}, {2, 0} };
	// square 5x5
	range[3] = {
		{2, -2}, {2, -1}, {2, 1}, {2, 2},
		{1, -2}, {-1, -2}, {1, 2}, {-1, 2},
		{-2, -2}, {-2, -1}, {-2, 1}, {-2, 2},
	};

	//for (int i = 0; i < 25; ++i)
	//{
	//	Sprite* skillSpriteArr = new Sprite();
	//	Animator* skillEffectArr = new Animator();
	//	skillEffectArr->SetTarget(skillSpriteArr);
	//	skillEffectArr->AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_Skill_Effect"));

	//	skillSprite.push_back(skillSpriteArr);
	//	skillEffect.push_back(skillEffectArr);
	//}
}

DanielSkill::~DanielSkill()
{
}

void DanielSkill::Init()
{
	Skill::Init();
	//for (int i = 0; i < 25; ++i)
	//{
	//	Sprite* skillSpriteArr = new Sprite();
	//	Animator* skillEffectArr = new Animator();
	//	skillEffectArr->SetTarget(skillSpriteArr);
	//	skillEffectArr->AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_Skill_Effect"));
	//	//{
	//	//	AnimationEvent ev;
	//	//	ev.clipId = "Daniel_Skill_Effect";
	//	//	ev.frame = 8;
	//	//	ev.onEvent = bind(&Daniel::OnCompleteSkill, this);
	//	//	skillEffectArr->AddEvent(ev);
	//	//}
	//	skillEffect.push_back(skillEffectArr);
	//	skillSprite.push_back(skillSpriteArr);
	//}
}

void DanielSkill::Update(float dt)
{
	Skill::Update(dt);
	//for (int i = 0; i < 25; ++i)
	//{
	//	skillEffect[i]->Update(dt);
	//}
}

void DanielSkill::Draw(RenderWindow& window)
{
	Skill::Draw(window);

	//for (auto skills : skillSprite)
	//{
	//	window.draw(*skills);
	//}
}

void DanielSkill::SetPos(const Vector2f& pos)
{
	Skill::SetPos(pos);
}

//void DanielSkill::SetState(AnimStates newState, SpriteObj* target, String t)
//{
//	Skill::SetState(newState);
//
//	/*if (currState == AnimStates::Skill)
//	{
//		vector<SpriteObj*>& mainGrid = GAME_MGR->GetMainGridRef();
//		Vector2i targetPos = GAME_MGR->PosToIdx(GetPos());
//		if (mainGrid[targetPos.y * 7 + targetPos.x + 1] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 1]->GetType().compare(t))
//		{
//			dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 1])->TakeDamage(this, false);
//			Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 1])->GetPos();
//			skillSprite[0]->setPosition(pos);
//			skillEffect[0]->Play("Daniel_Skill_Effect");
//		}
//		if (mainGrid[targetPos.y * 7 + targetPos.x - 1] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 1]->GetType().compare(t))
//		{
//			dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 1])->TakeDamage(this, false);
//			Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 1])->GetPos();
//			skillSprite[1]->setPosition(pos);
//			skillEffect[1]->Play("Daniel_Skill_Effect");
//		}
//		if (mainGrid[targetPos.y * 7 + targetPos.x + 7] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x + 7]->GetType().compare(t))
//		{
//			dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 7])->TakeDamage(this, false);
//			Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x + 7])->GetPos();
//			skillSprite[2]->setPosition(pos);
//			skillEffect[2]->Play("Daniel_Skill_Effect");
//		}
//		if (mainGrid[targetPos.y * 7 + targetPos.x - 7] != nullptr && !mainGrid[targetPos.y * 7 + targetPos.x - 7]->GetType().compare(t))
//		{
//			dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 7])->TakeDamage(this, false);
//			Vector2f pos = dynamic_cast<Character*>(mainGrid[targetPos.y * 7 + targetPos.x - 7])->GetPos();
//			skillSprite[3]->setPosition(pos);
//			skillEffect[3]->Play("Daniel_Skill_Effect");
//		}
//	}*/
//}

void DanielSkill::SetSkillRange(Vector2f startPos)
{
	applyArea.resize(0);
	Vector2i startCoord(GAME_MGR->PosToIdx(startPos));

	for (int i = 0; i < skillTier; i++)
	{
		for (auto& coord : range[i])
		{
			Vector2i tempCoord = startCoord + coord;

			if (tempCoord.x < 0 || tempCoord.x >= GAME_TILE_WIDTH ||
				tempCoord.y < 0 || tempCoord.y >= GAME_TILE_HEIGHT)
				continue ;

			applyArea.push_back(tempCoord);
		}
	}
}

void DanielSkill::CastSkill(Character* caster)
{
	SetSkillRange(caster->GetPos());

	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("Daniel_Skill_Effect"));
	animator.Play("Daniel_Skill_Effect");

	SetPos(caster->GetPos());

	for (auto& cell : applyArea)
	{
		GAME_MGR->rangePreview.Get()->Fire(GAME_MGR->IdxToPos(cell));
		SpriteObj* target = GAME_MGR->GetSpriteObjInMainGrid(cell);
		if (target != nullptr && !target->GetType().compare(caster->GetTarget()->GetType()))
		{
			//CLOG::PrintVectorState(GAME_MGR->PosToIdx(target->GetPos()), target->GetName());
			dynamic_cast<Character*>(target)->TakeDamage(caster, AttackTypes::Skill);
		}
	}
}