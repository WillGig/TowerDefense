#include "pch.h"
#include "WoodElf.h"

TowerDefense::Quirk::WoodElf::WoodElf()
	:Quirk("WoodElf")
{

}

void TowerDefense::Quirk::WoodElf::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamageModifier(h.GetTower()->GetDamageModifier(Tower::DamageType::PHYSICAL) + 1, Tower::DamageType::PHYSICAL);
	h.GetTower()->SetAttackTime(h.GetTower()->GetAttackTime() * .9f);
}

std::string TowerDefense::Quirk::WoodElf::GetNameText(Gender gender) const
{
	static std::array<std::string, 10> maleNames = {
		"Ianven Springriver",
		"Qinhorn Oceansong",
		"Adgeiros Duskbeam",
		"Permaer Beechsmile",
		"Morsalor Greenpetal",
		"Mormaer Shildash",
		"Caryarus Sithas",
		"Leoneiros Galdrennish",
		"Cartoris Geidrissendroth",
		"Kelhorn Idronn"
	};

	static std::array<std::string, 10> femaleNames{
		"Bryleth Azureflower",
		"Zingwyn Fallsense",
		"Wyntris Poplarspell",
		"Helezorwyn Hazelhold",
		"Ularel Fogshard",
		"Caigwyn Cire",
		"Sharoris Isalkol",
		"Shavyre Quenocisco",
		"Trisdi Rornaxondron",
		"Aranala Geyshis"
	};

	if (gender == Gender::MALE)
		return maleNames[(int)(Random::GetFloat() * maleNames.size())];
	else
		return femaleNames[(int)(Random::GetFloat() * femaleNames.size())];
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::WoodElf::Clone()
{
	return std::make_shared<WoodElf>();
}