#include "AltarScene.h"
#include "Altar.h"
#include "Brazier.h"
#include "RssProgressWindow.h"

AltarScene::AltarScene()
	: Scene(Scenes::Battle), isAltarInstruction(false), isAltarExpInstruction(false),
	isAltarResetInstruction(false)
{
	altarInstruction.setTexture(*RESOURCE_MGR->GetTexture("graphics/Instruction/instruction_Altar.png"));
	altarInstruction.setScale(0.7f, 0.7f);
	altarInstruction.setPosition(5.f, 0.f);

	altarExpInstruction.setTexture(*RESOURCE_MGR->GetTexture("graphics/Instruction/instruction_AltarExp.png"));
	altarExpInstruction.setScale(0.7f, 0.7f);
	altarExpInstruction.setPosition(5.f, 0.f);

	altarResetInstruction.setTexture(*RESOURCE_MGR->GetTexture("graphics/Instruction/instruction_AltarReset.png"));
	altarResetInstruction.setScale(0.7f, 0.7f);
	altarResetInstruction.setPosition(5.f, 0.f);

	m_backGround = new SpriteObj();
	m_backGround->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/AltarBackGround.png"));
	m_backGround->SetPos({ 0.f,0.f });
	m_backGround->SetOrigin(Origins::TL);

	m_backButton.SetTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/BackButton.png"));
	m_backButton.SetPos({ GAME_SCREEN_WIDTH,0.f });
	m_backButton.SetOrigin(Origins::TR);

	levelBar = new RssProgressWindow();
	levelBar->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Altar/Icon_Level.png"));
	IntRect texRect = levelBar->GetTextureRect();
	levelBar->SetSize(Vector2f(120, texRect.height * 0.5f));
	levelBar->SetColor(Color(0, 0, 0, 100), Color::Green, Color::Black, 2.f);
	levelBar->SetProgressLocalPos(Vector2f(texRect.width * 0.5f, texRect.height * 0.25f));
	levelBar->SetLevelTextLocalPos(Vector2f(texRect.width * 0.5f + 4, texRect.height * 0.5f + 6));
	levelBar->SetPos(Vector2f(10, 10));

	objList.push_back(m_backGround);
	objList.push_back(levelBar);

	SetAltar();
	SetBrazier();
}

AltarScene::~AltarScene()
{
}

void AltarScene::Init()
{
	CLOG::Print3String("AltarScene Init");
}

void AltarScene::Release()
{
}

void AltarScene::Enter()
{
	CLOG::Print3String("AltarScene enter");

	GAME_MGR->GMReset();

	// level
	levelBar->SetLevel(GAME_MGR->accountInfo.level);
	// exp
	float value = GAME_MGR->accountInfo.level != 10 ? (float)GAME_MGR->accountInfo.exp / (float)GAME_MGR->accountExpLimit : 1.f;
	levelBar->GetProgressBar().SetProgressValue(value);

	AltarData data = GAME_MGR->altarData;
	int altarDataArray[4] = { data.mana, data.silver, data.physical, data.enforce };
	int count = 0;
	int sum = 0;
	for (auto altar : AltarList)
	{
		sum += altarDataArray[count];
		altar->SetGrade(altarDataArray[count++]);
		altar->Enter();
	}

	int temp = sum;
	int level = GAME_MGR->accountInfo.level * 2;

	brazier->SetNumbers(level, Utils::Clamp(level - temp, 0, 20));

	brazier->Enter();
}

void AltarScene::Exit()
{
	CLOG::Print3String("AltarScene exit");
}

void AltarScene::Update(float dt)
{
	if (!isAltarInstruction && InputMgr::GetMouseDown(Mouse::Button::Left) && altarInstruction.getGlobalBounds().contains(ScreenToWorldPos(InputMgr::GetMousePosI())))
	{
		isAltarInstruction = true;
	}
	else if (!isAltarExpInstruction && InputMgr::GetMouseDown(Mouse::Button::Left) && altarExpInstruction.getGlobalBounds().contains(ScreenToWorldPos(InputMgr::GetMousePosI())))
	{
		isAltarExpInstruction = true;
	}
	else if (!isAltarResetInstruction && InputMgr::GetMouseDown(Mouse::Button::Left) && altarResetInstruction.getGlobalBounds().contains(ScreenToWorldPos(InputMgr::GetMousePosI())))
	{
		isAltarResetInstruction = true;
	}

	Scene::Update(dt);

	if (InputMgr::GetKeyDown(Keyboard::Key::Escape))
	{
		SaveData();
		SCENE_MGR->ChangeScene(Scenes::Title);
	}

	if (isAltarInstruction && isAltarExpInstruction && isAltarResetInstruction)
	{
		if (InputMgr::GetMouseUp(Mouse::Left))
		{
			for (auto altar : AltarList)
			{
				brazier->PlayAni(altar->GetButtonCall(ScreenToWorldPos(InputMgr::GetMousePosI()), brazier->GetGrade()));
			}

			if (brazier->ClickButton(ScreenToWorldPos(InputMgr::GetMousePosI())))
			{
				for (auto altar : AltarList)
				{
					altar->ResetCount();
				}
			}
		}

		CallButton();
	}

	for (auto altar : AltarList)
	{
		altar->Update(dt);
	}

	brazier->Update(dt);
}

void AltarScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	m_backButton.Draw(window);
	for (auto obj : AltarList)
	{
		obj->Draw(window);
	}

	brazier->Draw(window);

	if (!isAltarInstruction)
	{
		window.draw(altarInstruction);
	}
	if (isAltarInstruction)
	{
		if (!isAltarExpInstruction)
			window.draw(altarExpInstruction);
	}
	if (isAltarExpInstruction)
	{
		if (!isAltarResetInstruction)
			window.draw(altarResetInstruction);
	}
}

void AltarScene::CallButton()
{
	if (m_backButton.GetGlobalBounds().contains(
		ScreenToWorldPos(InputMgr::GetMousePosI())))
	{
		if (InputMgr::GetMouseUp(Mouse::Left))
		{
			SaveData();
			SCENE_MGR->ChangeScene(Scenes::Title);
		}

		IsSize(true);
	}
	else
	{
		IsSize(false);
	}

}

void AltarScene::IsSize(bool is)
{
	if (is)
	{
		m_backButton.SetPos({ GAME_SCREEN_WIDTH,0.f });
		m_backButton.SetOrigin(Origins::TR);
		m_backButton.SetScale(1.2f, 1.2f);
	}
	else
	{
		m_backButton.SetPos({ GAME_SCREEN_WIDTH,0.f });
		m_backButton.SetOrigin(Origins::TR);
		m_backButton.SetScale(1.0f, 1.0f);
	}
}

void AltarScene::SetAltar()
{
	AltarData data = GAME_MGR->altarData;

	Altar* mana = new Altar({ GAME_SCREEN_WIDTH * 0.15f,GAME_SCREEN_HEIGHT * 0.1f }, 0, L"?????? ????", { 254,113,235,255 }, data.mana);
	AltarList.push_back(mana);

	Altar* silver = new Altar({ GAME_SCREEN_WIDTH * 0.62f,GAME_SCREEN_HEIGHT * 0.1f }, 1, L"?????? ????", { 255,230,98,255 }, data.silver);
	AltarList.push_back(silver);

	Altar* physical = new Altar({ GAME_SCREEN_WIDTH * 0.15f,GAME_SCREEN_HEIGHT * 0.50f }, 2, L"?????? ????", { 255,2,2,255 }, data.physical);
	AltarList.push_back(physical);

	Altar* enforce = new Altar({ GAME_SCREEN_WIDTH * 0.62f,GAME_SCREEN_HEIGHT * 0.50f }, 3, L"?????? ????", { 0,203,255,255 }, data.enforce);
	AltarList.push_back(enforce);
}

void AltarScene::SetBrazier()
{
	int temp = GAME_MGR->altarData.mana + GAME_MGR->altarData.silver + GAME_MGR->altarData.physical + GAME_MGR->altarData.enforce;
	int level = GAME_MGR->accountInfo.level * 2;

	if (temp > level)
	{
		for (auto init : AltarList)
		{
			init->SetGrade(0);
			init->Enter();
		}
	}

	brazier = new Brazier(level, Utils::Clamp(level - temp, 0, 20));
	brazier->Init();
}

void AltarScene::SaveData()
{
	AltarData data;
	data.mana = AltarList[0]->GetGrade();
	data.silver = AltarList[1]->GetGrade();
	data.physical = AltarList[2]->GetGrade();
	data.enforce = AltarList[3]->GetGrade();

	GAME_MGR->SaveAltarData(data.mana, data.silver, data.physical, data.enforce);
	GAME_MGR->LoadAltarEffectFromTable();
}