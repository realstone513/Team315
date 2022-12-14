#include "DivineShield.h"
#include "Character.h"
#include "rapidcsv.h"

DivineShield::DivineShield()
	:isPlaying(false)
{
}

DivineShield::~DivineShield()
{
}

void DivineShield::Enter()
{
	SetAni();
	SetTime();
	
}

void DivineShield::Init()
{
}

void DivineShield::Release()
{
}

void DivineShield::Update(float dt)
{
	if (isPlaying)
	{
		m_time -= dt;
		if (m_time < 0.f)
		{
			EndSkill();
			isPlaying = false;
		}
		m_DivineShield.Update(dt);
	}
}

void DivineShield::Draw(RenderWindow& window)
{
	if (!m_DivineShield.GetEndFrame())
	{
		SpriteObj::Draw(window);
	}
}

void DivineShield::SetTime()
{
	string panelDataPath = "data/PenalSkillTable.csv";

	rapidcsv::Document PanelDataDoc(panelDataPath, rapidcsv::LabelParams(0, -1));
	vector<float> time = PanelDataDoc.GetColumn<float>(7);
	m_Settime = time[4];
}

void DivineShield::SetAni()
{
	m_DivineShield.SetTarget(&sprite);
	m_DivineShield.AddClip(*RESOURCE_MGR->GetAnimationClip("Fx_DivineShield"));
	SetPos({ GAME_SCREEN_WIDTH * 0.5f ,GAME_SCREEN_HEIGHT * 0.5f + 200.f });
	SetScale(5.f, 5.f);
}

void DivineShield::SetIsPlaying(bool is)
{
	isPlaying = is;
}

void DivineShield::PlayingAni()
{
	isPlaying = true;
	m_DivineShield.Play("Fx_DivineShield");
	ActionSkill();
}

void DivineShield::ActionSkill()
{
	vector<SpriteObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	m_time = m_Settime;

	for (auto Player : mainGrid)
	{
		if (Player != nullptr && !Player->GetType().compare("Player"))
		{
			dynamic_cast<Character*>(Player)->SetInvincible(true);
		}
	}

	SOUND_MGR->Play("sounds/panel_Divine.ogg", 30.f, false);
}

void DivineShield::EndSkill()
{
	vector<SpriteObj*>& mainGrid = GAME_MGR->GetMainGridRef();

	for (auto Player : mainGrid)
	{
		if (Player != nullptr && !Player->GetType().compare("Player"))
		{
			dynamic_cast<Character*>(Player)->SetInvincible(false);
		}
	}
}
