#pragma once
#include "Include.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include "FileManager.h"
#include "ObjectPool.h"
#include "DamageText.h"
#include "RangePreview.h"

class BattleTracker;
class Character;
class DamageText;
class SpriteObj;
class Item;
class Skill;
class PowerUp;
class Tile;
class TileBackground;

class GameManager : public Singleton<GameManager>
{
protected:
	Chapters* m_PlayTileList;
	vector<vector<vector<vector<Tile*>>>> m_tiles;
	vector<TileBackground*> m_TileBackground;
	json backGroundDatas;
	json characterDatas;

	// Set monster character locate before battle with data imported from GameManager
	// When the game starts, the characters on the battleGrid are also taken.
	vector<SpriteObj*>* mainGrid;

	unordered_map<StatType, vector<float>> itemStatMap;
	map<string, WaveReward> waveRewardMap;
	map<string, vector<string>> powerUpStringMap;
	BattleTracker* battleTracker;

	// Additional level up probability when summon (Character)
	int extraLevelUpSummon;
	// Additional level up probability when combinate (Character)
	int extraLevelUpCombinate;
	// Additional grade up probability (Item)
	// int extraGradeUpChance;
	int battleCharacterCount;
	int startCoin;
	int currentCoin;
	int stageClearCoin;
	int clearCoinIncrease;
	int clearCoinIncreaseTerm;
	int bossStageClearBonus;

	int expansionCost;
	int expansionCount;
	int itemDropProbability;

	bool playingBattle;

public:
	GameManager();
	virtual ~GameManager();

	void GMInit();
	void GMReset();
	void GameEnd();
	void SaveAltarData(int mana, int silver, int physical, int enforce);
	void PrintDevInfo();

	const int GetCharacterCount() { return battleCharacterCount; }
	void SetCharacterCount(int newCharacterCount) { battleCharacterCount = newCharacterCount; }
	const int GetExtraLevelUpSummon() { return extraLevelUpSummon + altarData.twiceUpWhenSummon; }
	const int GetExtraLevelUpCombinate() { return extraLevelUpCombinate + altarData.twiceUpWhenCombine; }
	//const int GetExtraGradeUpChance() { return extraGradeUpChance; }

	Vector2i PosToIdx(Vector2f pos);
	Vector2f IdxToPos(Vector2i idx);
	Vector2f SnapToCoord(Vector2f pos);

	void SetTilesData();
	Tile* GetTile(int chap, int stage, int height, int width);
	vector<vector<Tile*>>* GetStage(int chap, int stage) { return &m_tiles[chap][stage]; }
	vector<TileBackground*> GetTileBackgroundList() { return m_TileBackground; };

	void SetBackGroundDatas();
	json GetBackGroundDatas();

	void CreatedTiles();
	void CreatedBackGround();
	Character* SpawnMonster(string name, int grade);
	Character* SpawnPlayer(int grade = 0, bool random = true, int idx = 0);
	
	Item* SpawnItem(int tier = 0, int typeIdx = -1);

	SpriteObj* GeneratePowerUp(PowerUpTypes puType, int tier = 0);
	SpriteObj* GeneratePowerUpbyMap(int idx, int tier);

	void MainGridReset();

	void SetCharacterDatas();
	json GetCharacterData(string name);

	void SetPlayingBattle(bool val) { playingBattle = val; }
	bool GetPlayingBattle() { return playingBattle; }

	vector<SpriteObj*>& GetMainGridRef() { return *mainGrid; }
	SpriteObj* GetSpriteObjInMainGrid(Vector2i coord);
	void RemoveFromMainGrid(SpriteObj* gameObj);

	int GetCurrentCoin() { return currentCoin; }
	int GetClearCoin();
	void TranslateCoin(int coin) { currentCoin += coin; }
	int GetCurrentExpansionCost() { return expansionCost * pow(2, expansionCount); }
	void TranslateExpansionCount(int val) { expansionCount += val; }

	int curChapIdx;
	int curStageIdx;

	int characterCost;
	int itemCost;

	float hpIncreaseRate;
	float adIncreaseRate;
	float apIncreaseRate;
	float asIncrease;

	int accountExpLimit;
	int cumulativeExp;

	ObjectPool<DamageText> damageUI;
	ObjectPool<RangePreview> rangePreview;
	queue<SpriteObj*> waitQueue;
	vector<PowerUp*> standingPowerUps;
	PowerUp* oneTimePowerUp;
	vector<Item*> drops;
	AltarData altarData;
	AccountInfo accountInfo;

	float manaPerAttack;
	float manaPerDamage;

	int powerUprerollCount;

	float GetManaPerAttack()
	{
		return manaPerAttack * (1.f + (0.01f * altarData.gainManaWhenAttack));
	}

	float GetManaPerDamage()
	{
		return manaPerDamage * (1.f + (0.01f * altarData.gainManaWhenDamage));
	}

	BattleTracker*& GetBattleTracker() { return battleTracker; }
	float GetItemStatMapElem(StatType statType, int grade);
	const vector<string>& GetPowerUpStrings(int tier);
	const WaveReward& GetWaveRewardMapElem();
	Item* CombineItem(Item* obj1, Item* obj2);
	Item* DropItem(Character* monster);
	void LoadAltarEffectFromTable();

	vector<int> comradeVec;
	vector<SpriteObj*> warriorsHeartVec;
	PowerUp* GetPowerUpByName(string name);
};

#define GAME_MGR (GameManager::GetInstance())

struct DamageData
{
	Character* character;
	float givenAD;
	float takenAD;
	float givenAP;
	float takenAP;
	DamageData(Character* character = nullptr)
		: character(character), givenAD(0.f), takenAD(0.f),
		givenAP(0.f), takenAP(0.f)
	{ 
	}
};

class BattleTracker
{
protected:
	vector<DamageData> datas;
	bool trackerMode; // true - given / false - taken

public:
	BattleTracker();
	~BattleTracker();

	void SetDatas();
	// true - given, false - taken / true - AD, false - AP
	void UpdateData(Character* character, float damage,
		bool givenOrTaken, bool dmgType);
	void PrintAllData();
	void SetTrackerMode(bool val) { trackerMode = val; }
	bool GetTrackerMode() { return trackerMode; }
	vector<DamageData>* GetDatas() { return &datas; }
	void DataSort();
};