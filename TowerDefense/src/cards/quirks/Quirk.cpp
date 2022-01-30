#include "pch.h"
#include "Quirk.h"

TowerDefense::Quirk::Quirk::Quirk(const std::string& name)
	:m_Name(name)
{}

void TowerDefense::Quirk::Quirk::Apply(TowerDefense::HeroCard& h) {}

void TowerDefense::Quirk::Quirk::OnPlay() {}

//Returns vector with 1 racial quirk, 2 positive quirks, and 1 negative quirk
std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Quirk::Quirk>>> TowerDefense::Quirk::Quirk::GenerateQuirks()
{
	auto quirks = std::make_shared<std::vector<std::shared_ptr<Quirk>>>();

	quirks->push_back(GetRandomRace());
	quirks->push_back(GetRandomPositiveQuirk(nullptr));
	quirks->push_back(GetRandomPositiveQuirk(quirks->at(quirks->size()-1)));
	quirks->push_back(GetRandomNegativeQuirk());

	return quirks;
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Quirk::GetQuirkFromName(const std::string name)
{
	if (name == "Human")
		return std::make_shared<Human>();
	else if (name == "Dwarf")
		return std::make_shared<Dwarf>();
	else if (name == "High Elf")
		return std::make_shared<HighElf>();
	else if (name == "Wood Elf")
		return std::make_shared<WoodElf>();
	else if (name == "Gnome")
		return std::make_shared<Gnome>();
	else if (name == "Orc")
		return std::make_shared<Orc>();
	else if (name == "Giant")
		return std::make_shared<Giant>();
	else if (name == "Battle Ready")
		return std::make_shared<BattleReady>();
	else if (name == "Explorer")
		return std::make_shared<Explorer>();
	else if (name == "Just Lucky")
		return std::make_shared<JustLucky>();
	else if (name == "Veteran")
		return std::make_shared<Veteran>();
	else if (name == "Farsighted")
		return std::make_shared<Farsighted>();
	else if (name == "Spellweaver")
		return std::make_shared<Spellweaver>();
	else if (name == "Fighter")
		return std::make_shared<Fighter>();
	else if (name == "Sage")
		return std::make_shared<Sage>();
	else if (name == "Berserker")
		return std::make_shared<Berserker>();
	else if (name == "Nearsighted")
		return std::make_shared<Nearsighted>();
	else
		return nullptr;
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Quirk::GetRandomRace()
{
	int quirkNumber = (int)(Random::GetFloat() * 7);
	if (quirkNumber == 0)
		return std::make_shared<Human>();
	else if (quirkNumber == 1)
		return std::make_shared<Dwarf>();
	else if (quirkNumber == 2)
		return std::make_shared<WoodElf>();
	else if (quirkNumber == 3)
		return std::make_shared<HighElf>();
	else if (quirkNumber == 4)
		return std::make_shared<Gnome>();
	else if (quirkNumber == 5)
		return std::make_shared<Orc>();
	else
		return std::make_shared<Giant>();
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Quirk::GetRandomPositiveQuirk(std::shared_ptr<Quirk> exclude)
{
	std::string name = "";

	if (exclude)
		name = exclude->GetName();

	auto options = std::vector<std::shared_ptr<Quirk>>();
	if(name != "Battle Ready")
		options.push_back(std::make_shared<BattleReady>());
	if (name != "Explorer")
		options.push_back(std::make_shared<Explorer>());
	if (name != "Veteran")
		options.push_back(std::make_shared<Veteran>());
	if (name != "Just Lucky")
		options.push_back(std::make_shared<JustLucky>());
	if (name != "Far Sighted")
		options.push_back(std::make_shared<Farsighted>());
	if (name != "Spellweaver")
		options.push_back(std::make_shared<Spellweaver>());
	if (name != "Sage")
		options.push_back(std::make_shared<Sage>());
	if (name != "Fighter")
		options.push_back(std::make_shared<Fighter>());
	if (name != "Berserker")
		options.push_back(std::make_shared<Berserker>());
	if (name != "Super Senses")
		options.push_back(std::make_shared<SuperSenses>());

	return options.at((int)(Random::GetFloat() * options.size()));
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Quirk::GetRandomNegativeQuirk()
{
	int quirkNumber = (int)(Random::GetFloat() * 1.0f);
	return std::make_shared<Nearsighted>();
}