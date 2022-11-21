#pragma once
#include "Include.h"
#include "Character.h"

class Goblin01 : public Character
{
protected:
public:
	Goblin01(int starNumber = 0);
	virtual ~Goblin01();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetState(AnimStates newState) override;
	
	void OnCompleteAttack();

	void UpdateIdle(float dt);
	void UpdateMoveToIdle(float dt);
	void UpdateMove(float dt);
	void UpdateAttack(float dt);
};