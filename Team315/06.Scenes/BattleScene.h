#pragma once
#include "Scene.h"
#include "Include.h"
#include "TileBackground.h"
#include "PanelSkill/Panel.h"
#include "InfoWindow.h"

class BattleSceneUI;
class SpriteObj;
class RectangleObj;
class VertexArrayObj;
class TextObj;

class BattleScene : public Scene
{
protected:
	BattleSceneUI* ui;
	Sprite castleBackground;

	Vector2f screenCenterPos;
	Vector2u screenSize;
	bool b_centerPos;
	float gameScreenBottomLimit;
	float gameScreenTopLimit;

	vector<vector<Tile*>>* curStage;
	vector<TileBackground*> curBackGround; 
	vector<RectangleObj>* pickAttackRangeRect;
	vector<SpriteObj*> flags;

	// bool playingBattle;

	// Create player character when summon (2x7) x(0, 6) y(16, 17)
	vector<SpriteObj*> prepareGrid;
	// draw rect only 2 x 7
	vector<RectangleObj*> prepareGridRect;

	// Set player character locate before battle (4x7) x(0, 6) y(10, 13)
	vector<SpriteObj*> battleGrid;

	SpriteObj* pick;
	Vector2f beforeDragPos;

	float gameEndTimer;

	int remainLife;

	bool stageEnd;
	bool stageResult;
	bool eventWindow;
	bool eventPreviewOn;
	int curEventTier;

	//Panel Skill
	Panel m_panel;

	TextObj* quickHandTimerText;
	float quickHandTimer;
	float quickHandDuration;

	//InfoWindow
	InfoWindow m_InfoWindow;
	bool isInfo;

	// instruction
	Sprite sumandcampInstruction;
	bool isSumAndCampInstruction;
	Sprite upgradeInstruction;
	bool isUpgradeInstruction;
	Sprite panelInstruction;
	bool isPanelInstruction;
	Sprite powerUpinstruction;
	bool isPowerUpInstruction;

public:
	BattleScene();
	virtual ~BattleScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void PutDownCharacter(vector<SpriteObj*>* start, vector<SpriteObj*>* dest,
		Vector2i startCoord, Vector2i destCoord);
	void PutDownItem(vector<SpriteObj*>* start, vector<SpriteObj*>* dest,
		Vector2i startCoord, Vector2i destCoord);

	void SetCurrentStage(int chap, int stage);
	void LoseFlag();
	void PickUpSpriteObj(SpriteObj* gameObj);
	void TranslateCoinState(float delta);
	int GetCurCharacterCount();
	void SetEventWindow(bool active) { eventWindow = active; }
	void ZoomControl(bool b_switch);
	void OneTimePowerUp();
	void BeginBattle();
};

int GetIdxFromCoord(Vector2i coord);
Vector2i GetCoordFromIdx(int idx, bool battle);
bool IsItem(SpriteObj* gameObj);
bool IsCharacter(SpriteObj* gameObj);
bool InPrepareGrid(Vector2i pos);
bool InBattleGrid(Vector2i pos);
int GetZeroElem(vector<SpriteObj*>& vec);