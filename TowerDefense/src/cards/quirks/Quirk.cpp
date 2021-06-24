#include "pch.h"
#include "Quirk.h"

TowerDefense::Quirk::Quirk::Quirk(const std::string& name)
	:m_Name(name)
{
}

void TowerDefense::Quirk::Quirk::Apply(TowerDefense::HeroCard& h)
{

}

void TowerDefense::Quirk::Quirk::OnPlay()
{

}

//Returns vector with 1 racial quirk, 2 positive quirks, and 1 negative quirk
std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Quirk::Quirk>>> TowerDefense::Quirk::Quirk::GenerateQuirks()
{
	auto quirks = std::make_shared<std::vector<std::shared_ptr<Quirk>>>();

	quirks->push_back(GetRandomQuirk(QuirkType::RACE, quirks));
	quirks->push_back(GetRandomQuirk(QuirkType::POSITIVE, quirks));
	quirks->push_back(GetRandomQuirk(QuirkType::POSITIVE, quirks));
	quirks->push_back(GetRandomQuirk(QuirkType::NEGATIVE, quirks));

	return quirks;
}

//Returns random quirk of specified type that is not already included in the exclude vector
//The racial quirk is not checked for exclusion, because there should never be two racial quirks on the same hero
std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Quirk::GetRandomQuirk(QuirkType type, std::shared_ptr<std::vector<std::shared_ptr<Quirk>>> exclude)
{
	std::shared_ptr<Quirk> q;
	if (type == QuirkType::RACE) 
	{
		int quirkNumber = (int)(Random::GetFloat() * 7);
		if (quirkNumber == 0)
			q = std::make_shared<Human>();
		else if (quirkNumber == 1)
			q = std::make_shared<Dwarf>();
		else if (quirkNumber == 2)
			q = std::make_shared<WoodElf>();
		else if (quirkNumber == 3)
			q = std::make_shared<HighElf>();
		else if (quirkNumber == 4)
			q = std::make_shared<Gnome>();
		else if (quirkNumber == 5)
			q = std::make_shared<Orc>();
		else if (quirkNumber == 6)
			q = std::make_shared<Giant>();
	}
	else if (type == QuirkType::POSITIVE) 
	{
		while (!q || Contains(exclude, q)) 
		{
			int quirkNumber = (int)(Random::GetFloat() * 9.0f);
			if (quirkNumber == 0)
				q = std::make_shared<BattleReady>();
			else if (quirkNumber == 1)
				q = std::make_shared<Explorer>();
			else if (quirkNumber == 2)
				q = std::make_shared<Veteran>();
			else if (quirkNumber == 3)
				q = std::make_shared<JustLucky>();
			else if (quirkNumber == 4)
				q = std::make_shared<Farsighted>();
			else if (quirkNumber == 5)
				q = std::make_shared<Spellweaver>();
			else if (quirkNumber == 6)
				q = std::make_shared<Sage>();
			else if (quirkNumber == 7)
				q = std::make_shared<Fighter>();
			else if (quirkNumber == 8)
				q = std::make_shared<Berserker>();
		}
	}
	else {
		while (!q || Contains(exclude, q)) 
		{
			int quirkNumber = (int)(Random::GetFloat() * 1.0f);
			if (quirkNumber == 0)
				q = std::make_shared<Nearsighted>();
		}
	}

	return q;
}

bool TowerDefense::Quirk::Quirk::Contains(std::shared_ptr<std::vector<std::shared_ptr<Quirk>>> quirks, std::shared_ptr<Quirk> q)
{
	for (unsigned int i = 0; i < quirks->size(); i++)
	{
		if (quirks->at(i)->GetName() == q->GetName())
			return true;
	}
	return false;
}