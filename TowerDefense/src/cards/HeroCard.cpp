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

TowerDefense::HeroCard::HeroCard(const std::string& name, const std::string& text, int cost, const std::string& image, std::shared_ptr<Tower::Tower> tower, std::shared_ptr<std::vector<std::shared_ptr<Quirk::Quirk>>> quirks)
	:TowerCard(name, cost, image, image), m_Level(1), m_CardText(text), m_Tower(tower), m_Quirks(quirks),
	m_NameText(std::make_unique<Text>(name, 0.0f, 0.0f, 10.0f, (float)m_Width)),
	m_BodyText(std::make_unique<Text>(text, 0.0f, 0.0f, 6.0f, (float)m_Width)),
	m_DetailedNameText(std::make_unique<Text>(name, 400.0f, 410.0f, 20.0f, (float)m_Width*2)),
	m_DetailedBodyText(std::make_unique<Text>(text, 400.0f, 270.0f, 12.0f, (float)m_Width*2))
{
	m_Exhausts = true;

	//Generate upgrade choices for tower
	m_Upgrades = m_Tower->GetUpgrades();

	//Apply effects of quirks
	if (m_Quirks)
	{
		for (unsigned int i = 0; i < m_Quirks->size(); i++) {
			m_Quirks->at(i)->Apply(*this);
		}
	}

	m_NameText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_BodyText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_DetailedNameText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_DetailedBodyText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::HeroCard::Render()
{
	TowerCard::Render();
	if (!m_OverBoard)
	{
		m_NameText->Render();
		m_BodyText->Render();
	}
}

void TowerDefense::HeroCard::RenderCardDetails()
{
	Card::RenderCardDetails();
	m_DetailedNameText->Render();
	m_DetailedBodyText->Render();
}

//Apply chosen upgrade and generate new choices
void TowerDefense::HeroCard::Upgrade()
{
	m_Level++;
	std::dynamic_pointer_cast<TowerDefense::Upgrade>(m_Upgrades->GetSelectedCard())->UpgradeHero(*this);
	m_Upgrades = m_Tower->GetUpgrades();
}

bool TowerDefense::HeroCard::Play()
{
	if (Board::Get().ValidPlace() && m_OverBoard) {
		for (unsigned int i = 0; i < m_Quirks->size(); i++) {
			m_Quirks->at(i)->OnPlay();
		}
		TowerCard::Play();
		return true;
	}
	return false;
}

void TowerDefense::HeroCard::SetX(float x)
{
	Entity::SetX(x);
	float xOff = 63.0f * -sin(m_Rotation * PI / 180.0f);
	float yOff = 63.0f * cos(m_Rotation * PI / 180.0f);
	m_NameText->SetPosition(m_X + xOff, m_Y + yOff, 0.0f);

	xOff = -15.0f * -sin(m_Rotation * PI / 180.0f);
	yOff = -15.0f * cos(m_Rotation * PI / 180.0f);
	m_BodyText->SetPosition(m_X + xOff, m_Y + yOff, 0.0f);
}

void TowerDefense::HeroCard::SetY(float y)
{
	Entity::SetY(y);
	float xOff = 63.0f * -sin(m_Rotation * PI / 180.0f);
	float yOff = 63.0f * cos(m_Rotation * PI / 180.0f);
	m_NameText->SetPosition(m_X + xOff, m_Y + yOff, 0.0f);

	xOff = -15.0f * -sin(m_Rotation * PI / 180.0f);
	yOff = -15.0f * cos(m_Rotation * PI / 180.0f);
	m_BodyText->SetPosition(m_X + xOff, m_Y + yOff, 0.0f);
}

void TowerDefense::HeroCard::SetRotation(float rotation)
{
	Entity::SetRotation(rotation);
	m_NameText->SetRotation(m_Rotation);
	float xOff = 63.0f * -sin(m_Rotation * PI / 180.0f);
	float yOff = 63.0f * cos(m_Rotation * PI / 180.0f);
	m_NameText->SetPosition(m_X + xOff, m_Y + yOff, 0.0f);

	m_BodyText->SetRotation(m_Rotation);
	xOff = -15.0f * -sin(m_Rotation * PI / 180.0f);
	yOff = -15.0f * cos(m_Rotation * PI / 180.0f);
	m_BodyText->SetPosition(m_X + xOff, m_Y + yOff, 0.0f);
}

//Create exact copy of hero card with copy of quirks and tower
std::shared_ptr<TowerDefense::Card> TowerDefense::HeroCard::Clone()
{
	std::shared_ptr<Tower::Tower> towerClone = m_Tower->Clone();
	auto hero = std::make_shared<HeroCard>(GetName(), m_CardText, m_Cost, m_Image->GetFile(), towerClone, nullptr);
	
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

	Quirk::Gender gender = 2.0f * Random::GetFloat() > 1.0f ? Quirk::Gender::MALE : Quirk::Gender::FEMALE;

	std::string name = GenerateName(gender);

	std::string text = GenerateText(quirks, heroClass);

	std::string image = GenerateImage(gender, quirks->at(0)->GetName());

	return std::make_shared<HeroCard>(name, text, cost, image, heroTower, quirks);
}

std::string TowerDefense::HeroCard::GenerateName(Quirk::Gender gender)
{
	static std::array<std::string, 17> maleNames = {
		"Philius",
		"Lionel",
		"Ahab",
		"Elvis",
		"Mac",
		"Richard",
		"Samuel",
		"Reginald",
		"Averbakh",
		"Donatello",
		"Harold",
		"Elmo",
		"Douglas",
		"Togrin",
		"Lance",
		"Ol' Micky",
		"Thorley"
	};

	static std::array<std::string, 16> femaleNames{
		"Gertrude",
		"Hannah",
		"Millie",
		"Susan",
		"Jane-a-lin",
		"Bertha",
		"Lilly",
		"Penelope",
		"Harriet",
		"Mildred",
		"Vivian",
		"Lydia",
		"Thorley",
		"Qiqi",
		"Alexandria",
		"Persephone"
	};

	if (gender == Quirk::Gender::MALE)
		return maleNames[(int)(Random::GetFloat() * maleNames.size())];
	else
		return femaleNames[(int)(Random::GetFloat() * femaleNames.size())];

}

//Generates info based on race, gender, and other quirks
//Race MUST be the first quirk in the quirks array
std::string TowerDefense::HeroCard::GenerateText(std::shared_ptr<std::vector<std::shared_ptr<Quirk::Quirk>>> quirks, const std::string& heroClass)
{
	std::string race = quirks->at(0)->GetName();
	
	std::string text = "Class:  " + heroClass + "\n";
	text += "Race:  " + race + "\n";

	for (unsigned int i = 1; i < quirks->size(); i++)
		text += quirks->at(i)->GetText() + "\n";

	return text;
}

//Returns an image associated with the given gender and race of the hero
std::string TowerDefense::HeroCard::GenerateImage(Quirk::Gender gender, const std::string& race)
{
	if (gender == Quirk::Gender::MALE)
	{
		if (race == "Human")
			return "res/textures/testTexture.png";
		else if (race == "Dwarf")
			return "res/textures/testTexture.png";
		else if (race == "HighElf")
			return "res/textures/testTexture.png";
		else if (race == "WoodElf")
			return "res/textures/testTexture.png";
		else if (race == "Gnome")
			return "res/textures/testTexture.png";
		else if (race == "Orc")
			return "res/textures/testTexture.png";
		else if (race == "Giant")
			return "res/textures/testTexture.png";
		std::cout << "Error Generating Hero: Could not find Race " << race << std::endl;
		return "";
	}
	else if (gender == Quirk::Gender::FEMALE)
	{
		if (race == "Human")
			return "res/textures/testTexture.png";
		else if (race == "Dwarf")
			return "res/textures/testTexture.png";
		else if (race == "HighElf")
			return "res/textures/testTexture.png";
		else if (race == "WoodElf")
			return "res/textures/testTexture.png";
		else if (race == "Gnome")
			return "res/textures/testTexture.png";
		else if (race == "Orc")
			return "res/textures/testTexture.png";
		else if (race == "Giant")
			return "res/textures/testTexture.png";
		std::cout << "Error Generating Hero: Could not find Race " << race << std::endl;
		return "";
	}
	std::cout << "Error Generating Hero: Could not find Gender " << (int)gender << std::endl;
	return "";
}