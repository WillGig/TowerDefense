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
	m_DetailedNameText(std::make_unique<Text>(name, 400.0f, 417.0f, 20.0f, (float)m_Width*2)),
	m_DetailedBodyText(std::make_unique<Text>(text, 400.0f, 215.0f, 12.0f, (float)m_Width*2))
{
	m_Exhausts = true;

	m_Tower->SetName(name);

	//Generate upgrade choices for tower
	m_Upgrades = m_Tower->GetUpgrades();

	//Apply effects of quirks
	if (m_Quirks)
	{
		for (unsigned int i = 0; i < m_Quirks->size(); i++) {
			m_Quirks->at(i)->Apply(*this);
			AddInfoCard(std::make_shared<InfoTile>(m_Quirks->at(i)->GetName()));
		}
	}
	AddInfoCard(std::make_shared<InfoTile>("exhaustInfo"));

	m_CostText = std::make_unique<Text>(std::to_string(m_Cost), 0.0f, 0.0f, 12.0f, (float)m_Width);
	m_DetailedCostText = std::make_unique<Text>(std::to_string(m_Cost), 320.0f, 412.0f, 24.0f, (float)m_Width);

	m_NameText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_CostText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_BodyText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_DetailedNameText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_DetailedCostText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_DetailedBodyText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_NameText->SetDropShadow(1.0f);
	m_CostText->SetDropShadow(1.0f);
	m_BodyText->SetDropShadow(0.5f);
	m_DetailedNameText->SetDropShadow(1.0f);
	m_DetailedCostText->SetDropShadow(1.0f);
	m_DetailedBodyText->SetDropShadow(1.0f);
}

void TowerDefense::HeroCard::Render()
{
	TowerCard::Render();
	if (!m_OverBoard)
	{
		m_NameText->Render();
		m_CostText->Render();
		m_BodyText->Render();
	}
}

void TowerDefense::HeroCard::RenderCardDetails()
{
	Card::RenderCardDetails();
	m_DetailedNameText->Render();
	m_DetailedCostText->Render();
	m_DetailedBodyText->Render();
}

//Apply chosen upgrade and generate new choices
void TowerDefense::HeroCard::Upgrade()
{
	m_Level++;
	std::dynamic_pointer_cast<TowerDefense::Upgrade>(m_Upgrades->GetSelectedCard())->UpgradeHero(*this);
	m_Upgrades = m_Tower->GetUpgrades();
}

bool TowerDefense::HeroCard::CanPlay()
{
	return Board::Get().ValidPlace() && m_OverBoard;
}

void TowerDefense::HeroCard::Play()
{
	for (unsigned int i = 0; i < m_Quirks->size(); i++) {
		m_Quirks->at(i)->OnPlay();
	}
	TowerCard::Play();
}

void TowerDefense::HeroCard::SetX(float x)
{
	Entity::SetX(x);
	UpdateTextPosition();
}

void TowerDefense::HeroCard::SetY(float y)
{
	Entity::SetY(y);
	UpdateTextPosition();
}

void TowerDefense::HeroCard::SetRotation(float rotation)
{
	Entity::SetRotation(rotation);
	UpdateTextPosition();

	m_NameText->SetRotation(m_Rotation);
	m_CostText->SetRotation(m_Rotation);
	m_BodyText->SetRotation(m_Rotation);
}

void TowerDefense::HeroCard::UpdateTextPosition()
{
	float rot = m_Rotation * PI / 180.0f;

	float xOff = 59.0f * -sin(rot);
	float yOff = 59.0f * cos(rot);
	m_NameText->SetPosition(m_X + xOff, m_Y + yOff, 0.0f);

	xOff = 57 * -sin(rot) - 40 * cos(rot);
	yOff = 57 * cos(rot) - 40 * sin(rot);
	m_CostText->SetPosition(m_X + xOff, m_Y + yOff, 0.0f);

	xOff = -15.0f * -sin(rot);
	yOff = -43.0f * cos(rot);
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

void TowerDefense::HeroCard::SetQuirks(std::shared_ptr<std::vector<std::shared_ptr<Quirk::Quirk>>> quirks)
{
	m_Quirks = quirks;
	for (unsigned int i = 0; i < m_Quirks->size(); i++)
		AddInfoCard(std::make_shared<InfoTile>(m_Quirks->at(i)->GetName()));
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
		cost = 50;
	}
	else if (towerClass == 3) {
		heroTower = std::make_shared<Tower::Cleric>();
		heroClass = "Cleric";
		cost = 50;
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
	static std::array<std::string, 20> maleNames = {
		"Philius",
		"Lionel",
		"Ahab",
		"Elvis",
		"Mac",
		"Richard",
		"Samuel",
		"Gerald",
		"Bach",
		"Donny",
		"Harold",
		"Elmo",
		"Douglas",
		"Togrin",
		"Stheno",
		"Zirez",
		"Atty",
		"Lance",
		"Micky",
		"Thorley"
	};

	static std::array<std::string, 16> femaleNames{
		"Gerd",
		"Hannah",
		"Millie",
		"Susan",
		"Janice",
		"Bertha",
		"Lilly",
		"Penelope",
		"Harriet",
		"Mildred",
		"Vivian",
		"Lydia",
		"Thorley",
		"Qiqi",
		"Alex",
		"Pixie"
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
		text += quirks->at(i)->GetName() + "\n";

	return text;
}

//Returns an image associated with the given gender and race of the hero
std::string TowerDefense::HeroCard::GenerateImage(Quirk::Gender gender, const std::string& race)
{
	if (gender == Quirk::Gender::MALE)
	{
		if (race == "Human")
			return "humanMale";
		else if (race == "Dwarf")
			return "dwarfMale";
		else if (race == "High Elf")
			return "highElfMale";
		else if (race == "Wood Elf")
			return "woodElfMale";
		else if (race == "Gnome")
			return "gnomeMale";
		else if (race == "Orc")
			return "orcMale";
		else if (race == "Giant")
			return "giantMale";
		std::cout << "Error Generating Hero: Could not find Race " << race << std::endl;
		return "";
	}
	else if (gender == Quirk::Gender::FEMALE)
	{
		if (race == "Human")
			return "humanFemale";
		else if (race == "Dwarf")
			return "dwarfFemale";
		else if (race == "High Elf")
			return "highElfFemale";
		else if (race == "Wood Elf")
			return "woodElfFemale";
		else if (race == "Gnome")
			return "gnomeFemale";
		else if (race == "Orc")
			return "orcFemale";
		else if (race == "Giant")
			return "giantFemale";
		std::cout << "Error Generating Hero: Could not find Race " << race << std::endl;
		return "";
	}
	std::cout << "Error Generating Hero: Could not find Gender " << (int)gender << std::endl;
	return "";
}