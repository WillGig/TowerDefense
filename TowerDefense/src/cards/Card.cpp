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
	int randomCard = (int)(Random::GetFloat()*15);

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
	else if (randomCard == 13)
		return std::make_shared<RangerCard>();
	else
		return std::make_shared<ScholarCard>();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Card::GetUncommonCard()
{
	int randomCard = (int)(Random::GetFloat() * 13);

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
	else if (randomCard == 11)
		return std::make_shared<EchoLocation>();
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

std::shared_ptr<TowerDefense::Card> TowerDefense::Card::GetCardFromName(const std::string& name)
{
	if (name == "Focus")
		return std::make_shared<Focus>(false);
	else if (name == "Archer")
		return std::make_shared<ArcherCard>();
	else if (name == "Pot of Greed")
		return std::make_shared<PotOfGreed>();
	else if (name == "Double")
		return std::make_shared<Double>();
	else if (name == "Fire Ball")
		return std::make_shared<FireBall>();
	else if (name == "Frost Ball")
		return std::make_shared<FrostBall>();
	else if (name == "Poison Ball")
		return std::make_shared<PoisonBall>();
	else if (name == "Lightning")
		return std::make_shared<Lightning>();
	else if (name == "Sift")
		return std::make_shared<Sift>();
	else if (name == "Reflect")
		return std::make_shared<Reflect>();
	else if (name == "Skim")
		return std::make_shared<Skim>();
	else if (name == "Refresh")
		return std::make_shared<Refresh>();
	else if (name == "Center")
		return std::make_shared<Center>();
	else if (name == "Wizard")
		return std::make_shared<WizardCard>();
	else if (name == "Alchemist")
		return std::make_shared<AlchemistCard>();
	else if (name == "Bard")
		return std::make_shared<BardCard>();
	else if (name == "Ranger")
		return std::make_shared<RangerCard>();
	else if (name == "Monk")
		return std::make_shared<ScholarCard>();
	else if (name == "Gather")
		return std::make_shared<Gather>();
	else if (name == "Concentrate")
		return std::make_shared<Concentrate>();
	else if (name == "Recharge")
		return std::make_shared<Recharge>();
	else if (name == "Attain")
		return std::make_shared<Attain>();
	else if (name == "Strong Poisons")
		return std::make_shared<StrongPoisons>();
	else if (name == "Envenom")
		return std::make_shared<Envenom>();
	else if (name == "Life Aura")
		return std::make_shared<LifeAura>();
	else if (name == "Stunning Strikes")
		return std::make_shared<StunningStrikes>();
	else if (name == "The Floor is Lava")
		return std::make_shared<TheFloorIsLava>();
	else if (name == "Giant")
		return std::make_shared<GiantCard>();
	else if (name == "Cleric")
		return std::make_shared<ClericCard>();
	else if (name == "Paladin")
		return std::make_shared<PaladinCard>();
	else if (name == "Ren")
		return std::make_shared<Ren>();
	else if (name == "Surge")
		return std::make_shared<Surge>();
	else if (name == "Mass Stun")
		return std::make_shared<MassStun>();
	else if (name == "Explosive Strikes")
		return std::make_shared<ExplosiveStrikes>();
	else if (name == "Lightning Storm")
		return std::make_shared<LightningStorm>();
	else if (name == "Echo Location")
		return std::make_shared<EchoLocation>();
	else
		return nullptr;
}