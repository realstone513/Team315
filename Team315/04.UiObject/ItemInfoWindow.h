#pragma once
#include "SpriteGrid.h"

class BackrectText;
class Item;
class PowerUp;

class ItemInfoWindow : public SpriteGrid
{
protected:
	BackrectText* name;
	BackrectText* status;
	Sprite itemSprite;
	Sprite statSprite;
	BackrectText* additional;
	bool needAdditional;

public:
	ItemInfoWindow(float x = 0, float y = 0);
	virtual ~ItemInfoWindow();

	virtual void Draw(RenderWindow& window) override;
	virtual void SetOrigin(Origins origin) override;
	virtual void SetPos(const Vector2f& pos) override;
	void SetItem(Item* item);
	void SetPowerUp(PowerUp* power);
};