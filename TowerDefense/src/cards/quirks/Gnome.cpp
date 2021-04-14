#include "pch.h"
#include "Gnome.h"

TowerDefense::Quirk::Gnome::Gnome()
	:Quirk("Gnome")
{

}

void TowerDefense::Quirk::Gnome::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamageModifier(h.GetTower()->GetDamageModifier(Tower::DamageType::MAGIC) + 2, Tower::DamageType::MAGIC);
}

std::string TowerDefense::Quirk::Gnome::GetNameText(Gender gender) const
{
	static std::array<std::string, 10> maleNames = {
		"Fellin Puddleflow",
		"Jorpip Fizzleblock",
		"Lomin Silverspan",
		"Fellin Billowcord",
		"Bilwin Strongpeak",
		"Toji Panggerig",
		"Calner Tircotenend",
		"Zilner Segglesaggle",
		"Felpip Hinponerall",
		"Manmorn Rappull"
	};

	static std::array<std::string, 10> femaleNames{
		"Trifi Boldmane",
		"Rosibi Glitterfirn",
		"Selsany Fizzlecase",
		"Sadira Lighttop",
		"Jelpine Flickerbrand",
		"Faewyn Lucklediser",
		"Prinoa Haenbadora",
		"Grenfyx Fopplefopple",
		"Inaxi Sonber",
		"Dolin Melnadas"
	};

	if (gender == Gender::MALE)
		return maleNames[(int)(Random::GetFloat() * maleNames.size())];
	else
		return femaleNames[(int)(Random::GetFloat() * femaleNames.size())];
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Gnome::Clone()
{
	return std::make_shared<Gnome>();
}