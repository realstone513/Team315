#pragma once
#include "Character.h"

class Goblin01 : public Character
{
protected:
public:
	Goblin01(bool mode = false, bool useExtraUpgrade = false, int starGrade = 0);
	virtual ~Goblin01();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};