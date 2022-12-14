#pragma once
#include "UIMgr.h"

class BattlePanel;
class BackrectText;
class Character;
class DamageTrackerUI;
class EventPanel;
class Item;
class ItemInfoWindow;
class StatPopupWindow;
class RectangleObj;
class VertexArrayObj;

class BattleSceneUI : public UIMgr
{
protected:
	BattlePanel* panel;
	StatPopupWindow* statPopup;
	vector<ItemInfoWindow*> itemPopups;
	BackrectText* stageEndWindow;
	Sprite stageEndWindowSprite;
	bool b_stageEndPopup;
	DamageTrackerUI* dmgTrackerUI;
	EventPanel* eventPanel;

public:
	BattleSceneUI(Scene* scene);
	virtual ~BattleSceneUI();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	BattlePanel* GetPanel() { return panel; }
	DamageTrackerUI* GetTracker() { return dmgTrackerUI; }
	EventPanel* GetEventPanel() { return eventPanel; }
	void CreateBackground(VertexArrayObj* vao, int rows, int cols, float quadWidth, float quadHeight);

	void SetStatPopup(bool active, Vector2f viewCenter,
		Character* character = nullptr, Vector2f pos = {0, 0});
	void SetItemPopup(bool active, Vector2f viewCenter,
		Item* item = nullptr, Vector2f pos = { 0, 0 });
	void SetStageEndWindow(bool active, bool result = false);
	void SetEventPanel(bool active, int tier = 0, EventType eType = EventType::None);
};