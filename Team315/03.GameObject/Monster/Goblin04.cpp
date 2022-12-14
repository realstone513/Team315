#include "Goblin04.h"

Goblin04::Goblin04(bool mode, bool useExtraUpgrade, int starGrade)
	: Character(mode, useExtraUpgrade, starGrade)
{
	SetType("Monster");
	SetName("Goblin04");
	resStringTypes.insert({ ResStringType::Idle,"goblin04_Idle" });
	resStringTypes.insert({ ResStringType::DownIdle,"goblin04_DownIdle" });
	resStringTypes.insert({ ResStringType::LeftIdle,"goblin04_LeftIdle" });
	resStringTypes.insert({ ResStringType::RightIdle,"goblin04_RightIdle" });
	resStringTypes.insert({ ResStringType::UpIdle,"goblin04_UpIdle" });

	resStringTypes.insert({ ResStringType::DownMove,"goblin04_DownMove" });
	resStringTypes.insert({ ResStringType::LeftMove,"goblin04_LeftMove" });
	resStringTypes.insert({ ResStringType::RightMove,"goblin04_RightMove" });
	resStringTypes.insert({ ResStringType::UpMove,"goblin04_UpMove" });

	resStringTypes.insert({ ResStringType::DownAttack,"goblin04_DownAttack" });
	resStringTypes.insert({ ResStringType::LeftAttack,"goblin04_LeftAttack" });
	resStringTypes.insert({ ResStringType::RightAttack,"goblin04_RightAttack" });
	resStringTypes.insert({ ResStringType::UpAttack,"goblin04_UpAttack" });

	resStringTypes.insert({ ResStringType::atkSound, "sounds/monster_greatsword.wav" });
}

Goblin04::~Goblin04()
{
}

void Goblin04::Init()
{
	Character::Init();
}

//void Goblin04::SetState(AnimStates newState)
//{
//	Character::SetState(newState);
//
//	switch (currState)
//	{
//	case AnimStates::Idle:
//		animator.Play("goblin04_Idle");
//		break;
//	case AnimStates::MoveToIdle:
//		if (lastDirection.y)
//		{
//			animator.Play((lastDirection.y > 0.f) ? "goblin04_DownIdle" : "goblin04_UpIdle");
//		}
//		if (lastDirection.x)
//		{
//			animator.Play((lastDirection.x > 0.f) ? "goblin04_RightIdle" : "goblin04_LeftIdle");
//		}
//		break;
//	case AnimStates::Move:
//		if (direction.y)
//		{
//			animator.Play((direction.y > 0.f) ? "goblin04_DownMove" : "goblin04_UpMove");
//		}
//		if (direction.x)
//		{
//			animator.Play((direction.x > 0.f) ? "goblin04_RightMove" : "goblin04_LeftMove");
//		}
//		break;
//	case AnimStates::Attack:
//		if (lastDirection.x)
//		{
//			SOUND_MGR->Play("sounds/monster_greatsword.wav", 20.f, false);
//			animator.Play((lastDirection.x > 0.f) ? "goblin04_RightAttack" : "goblin04_LeftAttack");
//		}
//		if (lastDirection.y)
//		{
//			SOUND_MGR->Play("sounds/monster_greatsword.wav", 20.f, false);
//			animator.Play((lastDirection.y > 0.f) ? "goblin04_DownAttack" : "goblin04_UpAttack");
//		}
//		break;
//	}
//}

void Goblin04::Update(float dt)
{
	Character::Update(dt);

	//switch (currState)
	//{
	//case AnimStates::Idle:
	//	UpdateIdle(dt);
	//	break;
	//case AnimStates::MoveToIdle:
	//	UpdateMoveToIdle(dt);
	//	break;
	//case AnimStates::Move:
	//	UpdateMove(dt);
	//	break;
	//case AnimStates::Attack:
	//	UpdateAttack(dt);
	//	break;
	//}
	//animator.Update(dt);
	//
	//if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
	//{
	//	lastDirection = direction;
	//}
	//direction = { 0.f, 0.f };
}

void Goblin04::Draw(RenderWindow& window)
{
	Character::Draw(window);
}

void Goblin04::SetPos(const Vector2f& pos)
{
	Character::SetPos(pos);
}

//void Goblin04::OnCompleteAttack()
//{
//	SetState(AnimStates::MoveToIdle);
//}
//
//void Goblin04::OnCompleteSkill()
//{
//}
//
//void Goblin04::UpdateIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Goblin04::UpdateMoveToIdle(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) || !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::Move);
//		return;
//	}
//}
//
//void Goblin04::UpdateMove(float dt)
//{
//	if (Utils::EqualFloat(direction.x, 0.f) && Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//		return;
//	}
//	if (!Utils::EqualFloat(direction.y, lastDirection.y))
//	{
//		animator.Play((direction.y > 0.f) ? "goblin04_DownMove" : "goblin04_UpMove");
//	}
//	if (!Utils::EqualFloat(direction.x, lastDirection.x))
//	{
//		animator.Play((direction.x > 0.f) ? "goblin04_RightMove" : "goblin04_LeftMove");
//	}
//}
//
//void Goblin04::UpdateAttack(float dt)
//{
//	if (!Utils::EqualFloat(direction.x, 0.f) && !Utils::EqualFloat(direction.y, 0.f))
//	{
//		SetState(AnimStates::MoveToIdle);
//	}
//}