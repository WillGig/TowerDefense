#include "pch.h"
#include "Orc.h"

TowerDefense::Quirk::Orc::Orc()
	:Quirk("Orc")
{

}

void TowerDefense::Quirk::Orc::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamageModifier(h.GetTower()->GetDamageModifier(Tower::DamageType::PHYSICAL) + 3, Tower::DamageType::PHYSICAL);
	h.GetTower()->SetDamageModifier(h.GetTower()->GetDamageModifier(Tower::DamageType::MAGIC) - 1, Tower::DamageType::MAGIC);
}

std::string TowerDefense::Quirk::Orc::GetNameText(Gender gender) const
{
	static std::array<std::string, 10> maleNames = {
		"Bhak Black Bruiser",
		"Ghok Slave Destroyer",
		"Lakk The Cold",
		"Mok Pest Trampler",
		"Groggun The Noxious",
		"Omzub Gnome Cruncher",
		"Gohzuk The Venomous",
		"Lunull Flesh Killer",
		"Brodzol Venom Killer",
		"Makrokk The Gross"
	};

	static std::array<std::string, 10> femaleNames{
		"Ruh The Glorious",
		"Dan The Warped",
		"Vam The Grand",
		"Shik Flesh Glaive",
		"Anso Steel Despoiler",
		"Hiemdiz The Outlandish",
		"Ognuh Kill Slayer",
		"Hengaun Sorrow Destroyer",
		"Miemviv The Lethal",
		"Ode The Bloody"
	};

	if (gender == Gender::MALE)
		return maleNames[(int)(Random::GetFloat() * maleNames.size())];
	else
		return femaleNames[(int)(Random::GetFloat() * femaleNames.size())];
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Orc::Clone()
{
	return std::make_shared<Orc>();
}