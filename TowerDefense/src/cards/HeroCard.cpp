#include "pch.h"
#include "HeroCard.h"
#include "core/Player.h"
#include "core/Board.h"
#include "towers/Archer.h"
#include "towers/Wizard.h"
#include "towers/Bard.h"
#include "towers/Cleric.h"
#include "towers/Paladin.h"
#include "upgrades/Upgrade.h"

TowerDefense::HeroCard::HeroCard(const std::string& name, int cost, const std::string& image, std::shared_ptr<Tower::Tower> tower, std::shared_ptr<std::vector<std::shared_ptr<Quirk::Quirk>>> quirks)
	:TowerCard(name, cost, image, image), m_Level(1), m_Tower(tower), m_Quirks(quirks)
{
	m_Exhausts = true;

	//Apply effects of quirks
	if (m_Quirks)
	{
		for (unsigned int i = 0; i < m_Quirks->size(); i++) {
			m_Quirks->at(i)->Apply(*this);
		}
	}
	
	//Generate upgrade choices for tower
	m_Upgrades = m_Tower->GetUpgrades();
}

//Apply chosen upgrade and generate new choices
void TowerDefense::HeroCard::Upgrade()
{
	m_Level++;
	std::dynamic_pointer_cast<TowerDefense::Upgrade>(m_Upgrades->GetSelectedCard())->UpgradeHero(*this);
	m_Upgrades = m_Tower->GetUpgrades();
}

void TowerDefense::HeroCard::Play()
{
	if (Player::Get().GetEnergy() >= m_Cost && Board::Get().ValidPlace() && m_OverBoard) {
		for (unsigned int i = 0; i < m_Quirks->size(); i++) {
			m_Quirks->at(i)->OnPlay();
		}
	}
	TowerCard::Play();
}

//Create exact copy of hero card with copy of quirks and tower
std::shared_ptr<TowerDefense::Card> TowerDefense::HeroCard::Clone()
{
	std::shared_ptr<Tower::Tower> towerClone = m_Tower->Clone();
	auto hero = std::make_shared<HeroCard>(GetName(), m_Cost, m_Image->GetFile(), towerClone, nullptr);
	
	auto quirksClone = std::make_shared<std::vector<std::shared_ptr<Quirk::Quirk>>>();
	for (unsigned int i = 0; i < m_Quirks->size(); i++)
		quirksClone->push_back(m_Quirks->at(i)->Clone());

	hero->SetQuirks(quirksClone);
	hero->SetCost(m_Cost);
	hero->SetLevel(m_Level);

	return hero;
}

//Return a randomized hero 
std::shared_ptr<TowerDefense::HeroCard> TowerDefense::HeroCard::GenerateHero()
{
	std::shared_ptr<Tower::Tower> heroTower;
	int cost;
	std::string heroClass;

	int towerClass = (int)(Random::GetFloat() * 5);

	if (towerClass == 0) {
		heroTower = std::make_shared<Tower::Archer>();
		heroClass = "Archer";
		cost = 50;
	}
	else if (towerClass == 1) {
		heroTower = std::make_shared<Tower::Wizard>();
		heroClass = "Wizard";
		cost = 100;
	}
	else if (towerClass == 2) {
		heroTower = std::make_shared<Tower::Bard>();
		heroClass = "Bard";
		cost = 100;
	}
	else if (towerClass == 3) {
		heroTower = std::make_shared<Tower::Cleric>();
		heroClass = "Cleric";
		cost = 100;
	}
	else if (towerClass == 4) {
		heroTower = std::make_shared<Tower::Paladin>();
		heroClass = "Paladin";
		cost = 100;
	}

	auto quirks = Quirk::Quirk::GenerateQuirks();

	std::string name = GenerateName(quirks, heroClass);

	std::string image = "res/textures/testTexture.png";

	std::cout << "New Hero! " << name << std::endl;

	return std::make_shared<HeroCard>(name, cost, image, heroTower, quirks);
}

//Generates a random name based on race, gender, and other quirks
//Race MUST be the first quirk in the quirks array
std::string TowerDefense::HeroCard::GenerateName(std::shared_ptr<std::vector<std::shared_ptr<Quirk::Quirk>>> quirks, const std::string& heroClass)
{

	std::string race = quirks->at(0)->GetName();
	
	Quirk::Gender gender = 2.0f * Random::GetFloat() > 1.0f ? Quirk::Gender::MALE : Quirk::Gender::FEMALE;

	std::string name = quirks->at(0)->GetNameText(gender);

	name += " the ";

	for (unsigned int i = 1; i < quirks->size(); i++)
		name += quirks->at(i)->GetNameText(gender) + " ";

	name += race + " ";
	name += heroClass;

	return name;
}