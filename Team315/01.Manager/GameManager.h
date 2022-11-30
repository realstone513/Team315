#pragma once
#include "Include.h"
#include <vector>
#include <queue>
#include "FileManager.h"

struct DamageData;
class BattleTracker;
class GameObj;
class Tile;

class GameManager : public Singleton<GameManager>
{
protected:
	Chapters* m_PlayTileList;
	vector<vector<vector<vector<Tile*>>>> m_tiles;

	json characterDatas;

	vector<GameObj*> presetC;

	// Set monster character locate before battle with data imported from GameManager
	// When the game starts, the characters on the battleGrid are also taken.
	vector<GameObj*>* mainGrid;

	BattleTracker* battleTracker;

	// additional level up probability
	int extraLevelUpChance;
	int battleCharacterCount;
	int startCoin;
	int currentCoin;

public:
	GameManager();
	virtual ~GameManager();

	const int GetCharacterCount() { return battleCharacterCount; }
	const int GetExtraLevelUpChance() { return extraLevelUpChance; }

	Vector2i PosToIdx(Vector2f pos);
	Vector2f IdxToPos(Vector2i idx);
	Vector2f SnapToCoord(Vector2f pos);

	void SetTilesData();
	Tile* GetTile(int chap, int stage, int height, int width);
	vector<vector<Tile*>>* GetStage(int chap, int stage) { return &m_tiles[chap][stage]; }

	void CreatedTiles();
	GameObj* SpawnMonster(string name, int grade);
	GameObj* SpawnPlayer(string name, bool random, bool drawingOnBattle = true);
	GameObj* SpawnPlayer(bool random, bool drawingOnBattle = true);
	
	void Reset();

	void SetCharacterDatas();
	json GetCharacterData(string name);

	vector<GameObj*>& GetMainGridRef() { return *mainGrid; }

	int GetCurrentCoin() { return currentCoin; }
	void TranslateCoin(int coin) { currentCoin += coin; }

	const int characterCost;
	const int equipmentCost;

	BattleTracker*& GetTracker();
};

#define GAME_MGR (GameManager::GetInstance())

struct DamageData
{
	GameObj* character;
	float given;
	float receive;
	DamageData(GameObj* character = nullptr)
		: character(character), given(0.f), receive(0.f)
	{
	}
};

class BattleTracker
{
protected:
	vector<DamageData> datas;

public:
	BattleTracker();
	~BattleTracker();

	void SetDatas();
};