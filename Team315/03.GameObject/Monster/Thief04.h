#pragma once
#include "GameObj.h"

class Thief04 : public GameObj
{
protected:
public:
	Thief04(int starNumber = 0);
	virtual ~Thief04();

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

