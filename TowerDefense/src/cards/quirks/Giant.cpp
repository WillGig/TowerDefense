#include "pch.h"
#include "Giant.h"

TowerDefense::Quirk::Giant::Giant()
	:Quirk("Giant")
{

}

void TowerDefense::Quirk::Giant::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamageModifier(h.GetTower()->GetDamageModifier(Tower::DamageType::PHYSICAL) + 4, Tower::DamageType::PHYSICAL);
	h.GetTower()->SetAttackTime(h.GetTower()->GetAttackTime() * 1.2f);
}

std::string TowerDefense::Quirk::Giant::GetNameText(Gender gender) const
{
	static std::array<std::string, 10> maleNames = {
		"Dagan",
		"Asog",
		"Havog",
		"Clusog",
		"Nuzkrus",
		"Vedag",
		"Vlias",
		"Kesdus",
		"Metdus",
		"Dlodas"
	};

	static std::array<std::string, 10> femaleNames{
		"Moxkaos",
		"Hurog",
		"Vrexsag",
		"Blucrog",
		"Aredus",
		"Zukrym",
		"Dowas",
		"Saxkaos",
		"Tretdor",
		"Fregan"
	};

	if (gender == Gender::MALE)
		return maleNames[(int)(Random::GetFloat() * maleNames.size())];
	else
		return femaleNames[(int)(Random::GetFloat() * femaleNames.size())];
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Giant::Clone()
{
	return std::make_shared<Giant>();
}