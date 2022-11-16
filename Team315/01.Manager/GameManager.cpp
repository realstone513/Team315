#include "GameManager.h"
#include "Include.h"

GameManager::GameManager()
	: prepareSize(0), characterCount(10)
{
	CLOG::Print3String("GameManager Create");
	prepare.resize(PREPARE_SIZE, 0);
	preset.resize(PRESET_SIZE, 0);
}

GameManager::~GameManager()
{
}

void GameManager::EnterBattleScene()
{
	prepare.assign(PREPARE_SIZE, 0);
	prepareSize = 0;
}

void GameManager::SetPresetElem(int idx, int num)
{
	preset[idx] = num;
}

int GameManager::GetPrepareIdx()
{
	for (int idx = 0; idx < PREPARE_SIZE; idx++)
	{
		if (prepare[idx] == 0)
			return idx;
	}
	return -1; // fail
}

void GameManager::SetPrepare(vector<int>& set)
{
	prepare = set;
	int curSize = 0;
	for (auto& cell : prepare)
	{
		if (cell != 0)
			curSize++;
		else
			break;
	}
	prepareSize = curSize;
}

void GameManager::AddPrepare(int num)
{
	bool inputInPrepare = false;
	for (auto& cell : prepare)
	{
		if (cell == 0)
		{
			inputInPrepare = true;
			cell = num;
			prepareSize++;
			break;
		}
	}
	if (!inputInPrepare)
		waitQueue.push(num);
}

void GameManager::UpdatePrepare()
{
	if (waitQueue.empty())
		return;

	for (auto& cell : prepare)
	{
		if (cell != 0)
		{
			cell = waitQueue.front();
			waitQueue.pop();
			break;
		}
	}
};