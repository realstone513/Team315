#pragma once
#include "Character.h"

class Thief04 : public Character
{
protected:
public:
	Thief04(bool mode = false, bool useExtraUpgrade = false, int starGrade = 0);
	virtual ~Thief04();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;
};

