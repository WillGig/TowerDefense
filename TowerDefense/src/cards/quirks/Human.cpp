#include "pch.h"
#include "Human.h"

TowerDefense::Quirk::Human::Human()
	:Quirk("Human")
{

}

void TowerDefense::Quirk::Human::Apply(TowerDefense::HeroCard& h)
{
	h.SetCost((int)(h.GetCost() * 0.8f));
}

std::string TowerDefense::Quirk::Human::GetNameText(Gender gender) const
{
	static std::array<std::string, 16> maleNames = {
		"Ralun Khinu",
		"Barder Zahlu",
		"Voo Snakevale",
		"Grekrarn Frozengrove",
		"Glozil Ven",
		"Rer Chekruz",
		"Lelbon Riverbluff",
		"Strer Waterbluff",
		"Dun-Dur-Zek Sukrahrift",
		"Kod-Vad Hakdum",
		"Dridjedjask Ivzonovu",
		"Brarzik Edorga",
		"Fuy Zue",
		"Heh Seiy",
		"Sorfonel Sindolo",
		"Vevan Fosalbe"
	};

	static std::array<std::string, 16> femaleNames{
		"Soneifuh Doshad",
		"Aleh Delam",
		"Kezeirvil Summersplitter",
		"Sezneih Cragless",
		"Lena Desk",
		"Ro Rozeg",
		"Lithathe Twocrag",
		"Bafna Peacesong",
		"Hufrozhith Luldrikrek",
		"Vaha Ruthet",
		"Hafandru Ryenzelbitho",
		"Sharle Vukunzi",
		"Chiao Kua",
		"Cua Wan",
		"Qiencl Umani",
		"Ind Zesqorni"
	};

	if (gender == Gender::MALE)
		return maleNames[(int)(Random::GetFloat() * maleNames.size())];
	else
		return femaleNames[(int)(Random::GetFloat() * femaleNames.size())];
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Human::Clone()
{
	return std::make_shared<Human>();
}