#include "pch.h"
#include "Card.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "cards/Focus.h"
#include "cards/FireBall.h"
#include "cards/FrostBall.h"
#include "cards/PotOfGreed.h"
#include "cards/TowerCards.h"

float TowerDefense::Card::s_UncommonCardChance = .3f;
float TowerDefense::Card::s_RareCardChance = .02f;

TowerDefense::Card::Card(std::string name, int cost, const std::string& image, const std::string& upgradedImage)
	:Entity(110, 140, 0.0f, 0.0f, 0.0f, image, Type::CARD), m_Name(name), m_HandPosition(-1), m_Cost(cost), 
	m_Upgraded(false), m_OverBoard(false), m_Exhausts(false),
	m_DetailedImage(std::make_unique<Image>(image, 400.0f, 300.0f, 220, 280, 0.0f)),
	m_UpgradedImage(std::make_shared<Image>(upgradedImage, 0.0f, 0.0f, 110, 140, 0.0f)),
	m_InfoCards(std::make_unique<std::vector<std::shared_ptr<InfoTile>>>())
{
}

void TowerDefense::Card::Update()
{
	
}

void TowerDefense::Card::RenderUpgrade(float x, float y)
{
	m_UpgradedImage->SetPosition(x, y, 0.0f);
	m_UpgradedImage->Render();
}

void TowerDefense::Card::RenderCardDetails()
{
	m_DetailedImage->Render();
	for (unsigned int i = 0; i < m_InfoCards->size(); i++)
		m_InfoCards->at(i)->Render();
}

void TowerDefense::Card::Upgrade()
{
	m_Upgraded = true;
	SetImage(m_UpgradedImage);
	m_DetailedImage = std::make_unique<Image>(m_UpgradedImage->GetFile(), 400.0f, 300.0f, 220, 280, 0.0f);
}

void TowerDefense::Card::AddInfoCard(std::shared_ptr<InfoTile> cardInfo)
{
	if(m_InfoCards->size() > 2)
		cardInfo->SetPosition(650.0f, 400.0f  - 100.0f*(m_InfoCards->size()-3));
	else
		cardInfo->SetPosition(150.0f, 400.0f - 100.0f * m_InfoCards->size());
	m_InfoCards->push_back(cardInfo);
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Card::GetCommonCard()
{
	int randomCard = (int)(Random::GetFloat()*3);

	if (randomCard == 0) 
		return std::make_shared<Focus>(false);
	else if (randomCard == 1) 
		return std::make_shared<ArcherCard>();
	else
		return std::make_shared<PotOfGreed>();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Card::GetUncommonCard()
{
	int randomCard = (int)(Random::GetFloat() * 8);

	if (randomCard == 0)
		return std::make_shared<FireBall>();
	else if (randomCard == 1)
		return std::make_shared<FrostBall>();
	else if (randomCard == 2)
		return std::make_shared<BardCard>();
	else if (randomCard == 3)
		return std::make_shared<ClericCard>();
	else if (randomCard == 4)
		return std::make_shared<GiantCard>();
	else if (randomCard == 5)
		return std::make_shared<MonkCard>();
	else if (randomCard == 6)
		return std::make_shared<PaladinCard>();
	else
		return std::make_shared<WizardCard>();

}

std::shared_ptr<TowerDefense::Card> TowerDefense::Card::GetRareCard()
{
	return std::make_shared<GiantCard>();
}