#include "EventPanel.h"
#include "BackgroundText.h"
#include "Include.h"
#include "ItemInfoWindow.h"
#include "Scene.h"
#include "SpriteObj.h"
#include "SpriteGrid.h"
#include "BackrectText.h"
#include "Item/Item.h"
#include "PowerUp/PowerUp.h"
#include "DataTableMgr.h"
#include "StringTable.h"

EventPanel::EventPanel(Scene* scene)
	: parentScene(scene), previewOn(false), eventType(EventType::None),
	selectItem(false), selectIdx(0), curTier(0)
{
	SetSize(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT * 1.6f);
	SetFillColor(Color(0x0f, 0x0f, 0x0f, 200.f));

	previewButton = new SpriteObj();
	previewButton->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Pageup.png"));
	Vector2f textureSize(
		previewButton->GetTextureRect().width,
		previewButton->GetTextureRect().height);
	previewButton->SetHitbox(FloatRect(0, 0, textureSize.x, textureSize.y), Origins::TL);
	previewButton->SetScale(0.8f, 0.8f);
	previewButton->Init();

	title = new BackgroundText();
	title->SetTextStyle(Color::White, 25, Color::Black, 1.0f);
	title->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	title->SetTextLocalPos(Vector2f(0, 25.f));
	title->SetOrigin(Origins::TC);

	headLocalPos = Vector2f(GAME_SCREEN_WIDTH * 0.5f, 250.f);

	infoWindow = new ItemInfoWindow(200.f, 100.f);

	rerollButton = new BackrectText(150.f, 50.f);
	rerollButton->SetFillColor(Color(0xf7, 0xd3, 0x58));
	rerollButton->SetOutline(Color(0xa0, 0xa0, 0xa0), -5.0f);
	rerollButton->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	rerollButton->SetTextStyle(Color::White, 25.f, Color::Black, 2.f);
	rerollButton->SetTextLocalPos(Vector2f(0.f, -17.f));
	rerollButton->SetHitbox(FloatRect(0, 0, 150, 50), Origins::BC);

	selectButton = new BackrectText(150.f, 50.f);
	selectButton->SetFillColor(Color(0x58, 0x82, 0xfa));
	selectButton->SetOutline(Color(0xa0, 0xa0, 0xa0), -5.0f);
	selectButton->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	selectButton->SetTextStyle(Color::White, 25.f, Color::Black, 2.f);
	selectButton->SetTextLocalPos(Vector2f(0.f, -17.f));
	selectButton->SetHitbox(FloatRect(0, 0, 150, 50), Origins::BC);

	frames.resize(3);
	sprites.resize(3);

	for (int i = 0; i < 3; i++)
	{
		frames[i] = new SpriteObj();
		sprites[i] = new SpriteGrid(TILE_SIZE - 2, TILE_SIZE - 2);
		sprites[i]->SetFillColor(Color(0xf, 0x0f, 0x0f, 150.f));
		sprites[i]->SetHitbox(FloatRect(0, 0, TILE_SIZE, TILE_SIZE), Origins::MC);
	}
	Utils::SetOrigin(rerollCountSprite, Origins::BC);

	expResultWindow = new BackrectText(100.f, 50.f);
	expResultWindow->SetFont(*RESOURCE_MGR->GetFont("fonts/GodoB.ttf"));
	expResultWindow->SetTextLocalPos(Vector2f(0.f, -25.f));
	expResultWindow->SetTextStyle(Color::White, 25.f, Color::Black, 2.f);
	expResultWindow->SetOutline(Color(0x0f, 0x0f, 0x0f), 2.f);
	expResultWindow->SetFillColor(Color(0x0f, 0x0f, 0x0f, 150.f));
	expResultWindow->SetOrigin(Origins::BC);
}

EventPanel::~EventPanel()
{
}

void EventPanel::Init()
{
}

void EventPanel::Release()
{
}

void EventPanel::Reset()
{
	previewOn = false;
	eventType = EventType::None;
	selectItem = false;
	selectIdx = 0;
	curTier = 0;
	SetRerollText(2);
	rerollButton->SetFillColor(Color(0xf7, 0xd3, 0x58));
	rerollButton->SetHitBoxActive(true);
}

void EventPanel::Update(float dt)
{
	if (previewButton->CollideTest(parentScene->ScreenToWorldPos(InputMgr::GetMousePosI())))
	{
		if (InputMgr::GetMouseDown(Mouse::Left))
		{
			previewOn = true;
		}
	}

	if (previewOn)
	{
		if (InputMgr::GetMouseUp(Mouse::Left))
		{
			previewOn = false;
		}
	}

	int idx = 0;
	for (auto& item : sprites)
	{
		if (item->CollideTest(parentScene->ScreenToWorldPos(InputMgr::GetMousePosI())))
		{
			if (InputMgr::GetMouseDown(Mouse::Left))
			{
				selectItem = true;
				selectIdx = idx;

				item->SetScale(1.2f, 1.2f);
				item->SetOrigin(Origins::MC);

				frames[idx]->SetScale(1.2f, 1.2f);
				frames[idx]->SetOrigin(Origins::MC);

				if (eventType == EventType::Forge)
					infoWindow->SetItem(dynamic_cast<Item*>(items[idx]));
				else if (eventType == EventType::Power)
					infoWindow->SetPowerUp(dynamic_cast<PowerUp*>(items[idx]));

				SetPos(position);
			}
		}

		if (idx != selectIdx)
		{
			item->SetScale(1.f, 1.f);
			item->SetOrigin(Origins::MC);
			frames[idx]->SetScale(1.f, 1.f);
			frames[idx]->SetOrigin(Origins::MC);
		}
		idx++;
	}

	if (rerollButton->CollideTest(parentScene->ScreenToWorldPos(InputMgr::GetMousePosI())))
	{
		if (InputMgr::GetMouseDown(Mouse::Left))
		{
			if (eventType != EventType::Power)
				return;

			if (GAME_MGR->powerUprerollCount-- <= 0)
			{
				return;
			}

			SetRerollText(GAME_MGR->powerUprerollCount);
			selectItem = false;
			selectIdx = -1;
			previewOn = false;
			SetEventPanelType(eventType, curTier);
			if (eventType == EventType::Forge)
			{
				SOUND_MGR->Play("sounds/EquipReassessment.ogg", 40.f, false);
			}
			else if (eventType == EventType::Power)
			{
				SOUND_MGR->Play("sounds/PowerUpChange.ogg", 40.f, false);
			}
		}
	}

	if (selectButton->CollideTest(parentScene->ScreenToWorldPos(InputMgr::GetMousePosI())))
	{
		if (!selectItem)
			return;

		if (InputMgr::GetMouseDown(Mouse::Left))
		{
			int idx = 0;
			for (auto& item : items)
			{
				if (item != nullptr)
				{
					if (idx == selectIdx)
					{
						if (eventType == EventType::Forge)
						{
							SOUND_MGR->Play("sounds/EquipMake.ogg", 40.f, false);
							GAME_MGR->waitQueue.push(item);
						}
						else if (eventType == EventType::Power)
						{
							SOUND_MGR->Play("sounds/PowerUpSelect.ogg", 40.f, false);
							PowerUp* power = dynamic_cast<PowerUp*>(item);
							if (power->isStanding())
								GAME_MGR->standingPowerUps.push_back(power);
							else
								GAME_MGR->oneTimePowerUp = power;
						}
					}
					else
						delete item;
				}
				idx++;
			}
			items.clear();
			items.resize(3);

			eventType = EventType::None;
			curTier = 0;
			selectItem = false;
			selectIdx = 0;
			previewOn = false;
		}
	}
}

void EventPanel::Draw(RenderWindow& window)
{
	if (!previewOn)
	{
		RectangleObj::Draw(window);
		window.draw(head);
		title->Draw(window);
		if (eventType == EventType::Power)
		{
			rerollButton->Draw(window);
			window.draw(rerollCountSprite);
		}

		selectButton->Draw(window);

		if (selectItem)
			infoWindow->Draw(window);

		if (eventType != EventType::GameOver &&
			eventType != EventType::GameClear)
		{
			for (auto& itemSprite : sprites)
				itemSprite->Draw(window);

			for (auto& frame : frames)
				frame->Draw(window);
		}
		else
			expResultWindow->Draw(window);
	}
	if (eventType != EventType::GameOver &&
		eventType != EventType::GameClear)
		previewButton->Draw(window);
}

void EventPanel::SetOrigin(Origins origin)
{
}

void EventPanel::SetPos(const Vector2f& pos)
{
	RectangleObj::SetPos(pos);
	previewButton->SetPos(pos +
		Vector2f(GAME_SCREEN_WIDTH - previewButton->GetSize().x,
			GAME_SCREEN_HEIGHT * 1.5f + TILE_SIZE * 1.5f
			- previewButton->GetSize().y));
	head.setPosition(pos + headLocalPos);
	title->SetPos(pos + Vector2f(GAME_SCREEN_WIDTH * 0.5f,
		GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.f + 200.f));

	infoWindow->SetPos(pos + Vector2f(GAME_SCREEN_WIDTH * 0.5f - 100.f,
		GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.f + 300.f));

	expResultWindow->SetPos(pos + Vector2f(GAME_SCREEN_WIDTH * 0.5f,
		GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.f + 400.f));

	int posX = GAME_SCREEN_WIDTH * 0.25f;
	for (int i = 0; i < 3; i++)
	{
		frames[i]->SetPos(pos + Vector2f(posX,
			GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.f + 480.f));
		sprites[i]->SetPos(pos + Vector2f(posX,
			GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.f + 480.f));
		posX += GAME_SCREEN_WIDTH * 0.25f;
	}

	rerollButton->SetPos(pos +
		Vector2f(GAME_SCREEN_WIDTH * 0.5f,
			GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.f + 570.f));
	rerollCountSprite.setPosition(pos + Vector2f(GAME_SCREEN_WIDTH * 0.5f + 60,
		GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.f + 540.f));
	selectButton->SetPos(pos +
		Vector2f(GAME_SCREEN_WIDTH * 0.5f,
			GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.f + 630.f));
}

void EventPanel::SetEventPanelType(EventType eType, int tier)
{
	string key = "";
	string frameTexPath;
	vector<int> ranNums(3, -1);

	for (auto& item : items)
	{
		if (item != nullptr)
			delete item;
	}
	items.clear();
	items.resize(3);

	curTier = tier;
	eventType = eType;

	switch (eType)
	{
	case EventType::Forge:
		key = "ForgeTitle";
		headLocalPos.y = GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.5f + 250.f;
		head.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Icon_Forge.png"), true);
		title->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/BlueRibbon.png"), true);
		//rerollButton->SetString(STRING_TABLE->Get("EventForgeRerollText"));
		selectButton->SetString(STRING_TABLE->Get("EventForgeButtonText"));
		//rerollButton->SetOrigin(Origins::BC);
		selectButton->SetOrigin(Origins::BC);
		rerollButton->SetActive(false);

		frameTexPath = "graphics/battleScene/Item_Frame_";
		frameTexPath += (to_string(tier - 1) + ".png");
		for (int i = 0; i < 3; i++)
		{
			ranNums[i] = ranNums[i] == -1 ? Utils::RandomRange(0, 5) : ranNums[i];

			for (int j = 0; j <= i; j++)
			{
				if (i != j && ranNums[i] == ranNums[j])
				{
					ranNums[i] = -1;
					i--;
				}
			}
		}

		items.resize(3);
		for (int i = 0; i < 3; i++)
		{
			frames[i]->SetTexture(*RESOURCE_MGR->GetTexture(frameTexPath), true);
			frames[i]->SetOrigin(Origins::MC);
			items[i] = GAME_MGR->SpawnItem(tier - 1, ranNums[i]);
			sprites[i]->SetSpriteTexture(*RESOURCE_MGR->GetTexture(dynamic_cast<Item*>(items[i])->MakePath()), true);
			sprites[i]->SetOrigin(Origins::MC);
		}
		break;

	case EventType::Power:
		key = "PowerTitle";
		headLocalPos.y = GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.5f + 250.f;
		head.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Icon_Power.png"), true);
		title->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/RedRibbon.png"), true);
		rerollButton->SetActive(true);
		rerollButton->SetString(STRING_TABLE->Get("EventPowerRerollText"));
		selectButton->SetString(STRING_TABLE->Get("EventPowerButtonText"));
		rerollButton->SetOrigin(Origins::BC);
		selectButton->SetOrigin(Origins::BC);

		frameTexPath = "graphics/battleScene/Item_Frame_";
		for (int i = 0; i < 3; i++)
		{
			ranNums[i] = ranNums[i] == -1 ?
				Utils::RandomRange(0, CHARACTER_COUNT) : ranNums[i];

			for (int j = 0; j <= i; j++)
			{
				if (i != j && ranNums[i] == ranNums[j])
				{
					ranNums[i] = -1;
					i--;
				}
			}
		}

		items.resize(3);
		for (int i = 0; i < 3; i++)
		{
			items[i] = GAME_MGR->GeneratePowerUpbyMap(ranNums[i], tier);

			string tierNumber = to_string(dynamic_cast<PowerUp*>(items[i])->GetGrade());
			frames[i]->SetTexture(*RESOURCE_MGR->GetTexture(
				frameTexPath + tierNumber + ".png"), true);
			frames[i]->SetOrigin(Origins::MC);
			
			sprites[i]->SetSpriteTexture(*RESOURCE_MGR->GetTexture(dynamic_cast<PowerUp*>(items[i])->MakePath()), true);
			sprites[i]->SetOrigin(Origins::MC);
		}
		break;

	case EventType::GameOver:
		key = "GameOverTitle";
		headLocalPos.y = GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.5f + 200.f;
		head.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Icon_Defeat.png"), true);
		title->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/RedRibbon.png"), true);
		selectButton->SetString(STRING_TABLE->Get("EventGameEndButtonText"));
		selectButton->SetOrigin(Origins::BC);
		rerollButton->SetActive(false);
		break;

	case EventType::GameClear:
		key = "GameClearTitle";
		headLocalPos.y = GAME_SCREEN_HEIGHT * 0.5f + TILE_SIZE * 1.5f + 200.f;
		head.setTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/Icon_Clear.png"), true);
		title->SetTexture(*RESOURCE_MGR->GetTexture("graphics/battleScene/BlueRibbon.png"), true);
		selectButton->SetString(STRING_TABLE->Get("EventGameEndButtonText"));
		selectButton->SetOrigin(Origins::BC);
		rerollButton->SetActive(false);
		break;
	}

	float min = Utils::GetMinScaleRatioFromFloatRect(
		250.f, 250.f, (FloatRect)head.getTextureRect());
	head.setScale(min, min);
	Utils::SetOrigin(head, Origins::BC);

	title->SetString(STRING_TABLE->Get(key));
	title->SetOrigin(Origins::TC);
	SetPos(position);
}

void EventPanel::SetRerollText(int num)
{
	string path = "graphics/PanelSkill/BottomNumber_";
	rerollCountSprite.setTexture(*RESOURCE_MGR->GetTexture(path + to_string(num) + ".png"));

	if (num != 0)
		return;
	rerollButton->SetFillColor(Color(0xf0, 0xf0, 0xf0, 150.f));
	rerollButton->SetHitBoxActive(false);
}

void EventPanel::SetExpResultString(int num)
{
	wstring str = STRING_TABLE->Get("ExpText") + "+" + to_string(num);
	expResultWindow->SetString(str);
	expResultWindow->SetOrigin(Origins::BC);
}