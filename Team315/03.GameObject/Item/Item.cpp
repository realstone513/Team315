#include "Item.h"

Item::Item(int grade, ItemType type)
	: grade(grade), itemType(type), potential(0.f), statType(StatType::None)
{
	SetType("Item");
	sprite.setTexture(*RESOURCE_MGR->GetTexture(MakePath()), true);
	SetOrigin(Origins::BC);

	switch (itemType)
	{
	case ItemType::Armor:
		statType = StatType::HP;
		break;
	case ItemType::Bow:
		statType = StatType::AS;
		break;
	case ItemType::Staff:
		statType = StatType::AP;
		break;
	case ItemType::Sword:
		statType = StatType::AD;
		break;
	}
	//if (itemType != ItemType::Book)
		potential = GAME_MGR->GetItemStatMapElem(statType, grade);
}

Item::~Item()
{
}

void Item::Init()
{
	GameObj::Init();
}

void Item::Update(float dt)
{
}

void Item::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Item::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	sprite.setPosition(position + Vector2f(0, -10.f));
}

void Item::ApplyToCharacter(Character* character)
{
}

string Item::MakePath()
{
	string path = "graphics/battleScene/Item_";

	switch (itemType)
	{
	case ItemType::Armor:
		path += "Armor";
		break;
	case ItemType::Bow:
		path += "Bow";
		break;
	case ItemType::Staff:
		path += "Staff";
		break;
	case ItemType::Sword:
		path += "Sword";
		break;
	/*case ItemType::Book:
		path += "Book";
		break;*/
	default:
		cout << "fail" << endl;
		return "fail";
	}
	path += (to_string(grade) + ".png");
	return path;
}

bool Item::Upgrade()
{
	//int gradeLimit = itemType == ItemType::Book ? 2 : 3;
	int gradeLimit = 3;
	bool ret = false;
	if (grade < gradeLimit)
	{
		ret = true;
		grade++;
		sprite.setTexture(*RESOURCE_MGR->GetTexture(MakePath()), true);
		SetOrigin(Origins::BC);
		//if (itemType != ItemType::Book)
			potential = GAME_MGR->GetItemStatMapElem(statType, grade);
	}
	return ret;
}