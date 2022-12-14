#include "DamageText.h"

DamageText::DamageText()
{
}

DamageText::~DamageText()
{
}

void DamageText::SetDamageUI(Vector2f pos, StatType sType, float damage)
{
	switch (sType)
	{
	case StatType::AD:
		SetColor(Color::Red);
		break;
	case StatType::AP:
		SetColor(Color::Blue);
		break;
	case StatType::HP:
		SetColor(Color::Green);
		break;
	case StatType::None: // shield
		SetColor(Color::White);
		break;
	}
	float cSize = 14 + sqrt(damage) * 0.15f;

	SetCharacterSize(cSize);

	SetString(to_string((int)damage));
	Fire(pos, {0, -1}, 15.f, 10.f);
}