#include "SceneMgr.h"
#include "TitleScene.h"
#include "BattleScene.h"
#include "ToolScene.h"
#include "AltarScene.h"

Scenes SceneMgr::GetCurrScene() const
{
	return currScene;
}

Scene* SceneMgr::GetScene(Scenes scene)
{
	return sceneMap[scene];
}

bool SceneMgr::Init()
{
	sceneMap[Scenes::Title] = new TitleScene();
	sceneMap[Scenes::Battle] = new BattleScene();
	sceneMap[Scenes::Altar] = new AltarScene();
	sceneMap[Scenes::Tool] = new ToolScene();

	for (auto& i : sceneMap)
		i.second->Init();

	currScene = Scenes::Title;
	sceneMap[currScene]->Enter();
	return false;
}

void SceneMgr::ChangeScene(Scenes scene)
{
	sceneMap[currScene]->Exit();
	currScene = scene;
	sceneMap[currScene]->Enter();
}

void SceneMgr::Update(float dt)
{
	sceneMap[currScene]->Update(dt);
}

void SceneMgr::Draw(RenderWindow& window)
{
	sceneMap[currScene]->Draw(window);
}