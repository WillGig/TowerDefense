#include "pch.h"
#include "Card.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "SkillCards.h"
#include "AuraCards.h"
#include "cards/TowerCards.h"

float TowerDefense::Card::s_UncommonCardChance = .3f;
float TowerDefense::Card::s_RareCardChance = .02f;

TowerDefense::Card::Card(std::string name, CardType type, int cost, const std::string& image, const std::string& upgradedImage)
	:Entity(0.0f, 0.0f, 110, 140, 0.0f, image, Type::CARD), m_Name(name), m_CardType(type), m_HandPosition(-1), m_Cost(cost),
	m_Upgraded(false), m_OverBoard(false), m_Exhausts(false),
	m_UpgradedImage(std::make_shared<Image>(upgradedImage, 0.0f, 0.0f, 110, 140, 0.0f)),
	m_DetailedImage(std::make_unique<Image>(image, 400.0f, 300.0f, 220, 280, 0.0f)),
	m_Outline(std::make_unique<Image>("outline", 0.0f, 0.0f, 116, 146, 0.0f)),
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

void TowerDefense::Card::RenderOutline()
{
	m_Outline->SetPosition(m_X, m_Y, 0.0f);
	m_Outline->SetRotation(m_Rotation);
	m_Outline->Render();
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
	int randomCard = (int)(Random::GetFloat()*14);

	if (randomCard == 0)
		return std::make_shared<Double>();
	else if (randomCard == 1) 
		return std::make_shared<FireBall>();
	else if (randomCard == 2)
		return std::make_shared<FrostBall>();
	else if (randomCard == 3)
		return std::make_shared<PoisonBall>();
	else if (randomCard == 4)
		return std::make_shared<Lightning>();
	else if (randomCard == 5)
		return std::make_shared<Sift>();
	else if (randomCard == 6)
		return std::make_shared<Reflect>();
	else if (randomCard == 7)
		return std::make_shared<Skim>();
	else if (randomCard == 8)
		return std::make_shared<Refresh>();
	else if (randomCard == 9)
		return std::make_shared<Center>();
	else if (randomCard == 10)
		return std::make_shared<WizardCard>();
	else if (randomCard == 11)
		return std::make_shared<AlchemistCard>();
	else if (randomCard == 12)
		return std::make_shared<BardCard>();
	else
		return std::make_shared<MonkCard>();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Card::GetUncommonCard()
{
	int randomCard = (int)(Random::GetFloat() * 12);

	if (randomCard == 0)
		return std::make_shared<Gather>();
	else if (randomCard == 1)
		return std::make_shared<Concentrate>();
	else if (randomCard == 2)
		return std::make_shared<Recharge>();
	else if (randomCard == 3)
		return std::make_shared<Attain>();
	else if (randomCard == 4)
		return std::make_shared<StrongPoisons>();
	else if (randomCard == 5)
		return std::make_shared<Envenom>();
	else if (randomCard == 6)
		return std::make_shared<LifeAura>();
	else if (randomCard == 7)
		return std::make_shared<StunningStrikes>();
	else if (randomCard == 8)
		return std::make_shared<TheFloorIsLava>();
	else if (randomCard == 9)
		return std::make_shared<GiantCard>();
	else if (randomCard == 10)
		return std::make_shared<ClericCard>();
	else
		return std::make_shared<PaladinCard>();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Card::GetRareCard()
{
	int randomCard = (int)(Random::GetFloat() * 5);

	if (randomCard == 0)
		return std::make_shared<Ren>();
	else if (randomCard == 1)
		return std::make_shared<Surge>();
	else if(randomCard == 2)
		return std::make_shared<MassStun>();
	else if (randomCard == 3)
		return std::make_shared<ExplosiveStrikes>();
	else
		return std::make_shared<LightningStorm>();
}