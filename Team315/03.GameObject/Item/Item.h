#pragma once
#include "SpriteObj.h"
#include "Include.h"

class Item : public SpriteObj
{
protected:
	int grade;
	ItemType itemType;
	float potential;
	StatType statType;
	Sprite shadow;
	Vector2f spriteLocalPos;
	float delta;

	Vector2f destination;
	float moveSpeed;
	bool move;

public:
	Item(int grade = 0, bool useExtraChance = false, ItemType iType = ItemType::None);
	virtual ~Item();

	virtual void Init() override;
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	string MakePath();
	ItemType GetItemType() { return itemType; }
	int GetGrade() { return grade; }
	float GetPotential() { return potential; }
	StatType GetStatType() { return statType; }
	string GetStatTypeString();
	bool Upgrade();

	void SetDestination(Vector2f dest);
};