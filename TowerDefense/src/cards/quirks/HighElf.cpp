#include "pch.h"
#include "HighElf.h"

TowerDefense::Quirk::HighElf::HighElf()
	:Quirk("HighElf")
{

}

void TowerDefense::Quirk::HighElf::Apply(TowerDefense::HeroCard& h)
{
	h.GetTower()->SetDamageModifier(h.GetTower()->GetDamageModifier(Tower::DamageType::MAGIC) + 1, Tower::DamageType::MAGIC);
	h.GetTower()->SetAttackTime(h.GetTower()->GetAttackTime() * .9f);
}

std::string TowerDefense::Quirk::HighElf::GetNameText(Gender gender) const
{
	static std::array<std::string, 10> maleNames = {
		"Aranrian",
		"Urikul",
		"Sarnpeiros",
		"Marvan",
		"Kuonis",
		"Jorxis",
		"Araerta",
		"Panemin",
		"Elrotihr",
		"Wrugthas"
	};

	static std::array<std::string, 10> femaleNames{
		"Uraprana",
		"Eilprana",
		"Shacelle",
		"Xyrsanna",
		"Grumeiv",
		"Drisbynn",
		"Gylyana",
		"Mexis",
		"Caerastra",
		"Yllarastra"
	};

	if (gender == Gender::MALE)
		return maleNames[(int)(Random::GetFloat() * maleNames.size())];
	else
		return femaleNames[(int)(Random::GetFloat() * femaleNames.size())];
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::HighElf::Clone()
{
	return std::make_shared<HighElf>();
}