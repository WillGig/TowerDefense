#include "pch.h"
#include "Dwarf.h"

TowerDefense::Quirk::Dwarf::Dwarf()
	:Quirk("Dwarf")
{

}

void TowerDefense::Quirk::Dwarf::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamageModifier(h.GetTower()->GetDamageModifier(Tower::DamageType::PHYSICAL) + 2, Tower::DamageType::PHYSICAL);
}

std::string TowerDefense::Quirk::Dwarf::GetNameText(Gender gender) const
{
	static std::array<std::string, 10> maleNames = {
		"Malrus Boldhold",
		"Grandek Lighttale",
		"Hjalnam Steeleyes",
		"Bungurn Coldfound",
		"Thelram Hardmane",
		"Krammek Bankekonn",
		"Hulkohm Fomnugiln",
		"Balgram Taerthinag",
		"Berdir Fomnuhaln",
		"Gimnam Bobreken"
	};

	static std::array<std::string, 10> femaleNames{
		"Bralnera Trollkith",
		"Lesnura Mighthead",
		"Runris Bigfall",
		"Ingglia Broodback",
		"Brynwynn Bloodmane",
		"vBrytla Rallaver",
		"Belres Gankokog",
		"Brylnia Broderr",
		"Redthiel Laemnehark",
		"Elryl Hothgihorr"
	};

	if (gender == Gender::MALE)
		return maleNames[(int)(Random::GetFloat() * maleNames.size())];
	else
		return femaleNames[(int)(Random::GetFloat() * femaleNames.size())];
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Dwarf::Clone()
{
	return std::make_shared<Dwarf>();
}