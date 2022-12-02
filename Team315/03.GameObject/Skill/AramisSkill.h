#pragma once
#include "Skill.h"

class AramisSkill : public Skill
{
protected:

public:
	AramisSkill();
	virtual ~AramisSkill();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetPos(const Vector2f& pos) override;

	virtual void SetRotation(Vector2f dir);
	virtual void SetState(AnimStates newState);
};

