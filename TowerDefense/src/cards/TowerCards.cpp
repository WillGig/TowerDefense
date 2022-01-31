#include "pch.h"
#include "TowerCards.h"
#include "towers/Archer.h"
#include "towers/Wizard.h"
#include "Towers/Giant.h"
#include "towers/Alchemist.h"
#include "towers/Bard.h"
#include "towers/Cleric.h"
#include "towers/Paladin.h"
#include "towers/Scholar.h"
#include "towers/Ranger.h"

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::ArcherCard::GetTower()
{
	if (m_Upgraded)
		return std::make_shared<Tower::Archer>(30.0f, 125, 1.0f);
	else
		return std::make_shared<Tower::Archer>();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::ArcherCard::Clone()
{
	auto card = std::make_shared<ArcherCard>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::WizardCard::GetTower()
{
	if (m_Upgraded)
		return std::make_shared<Tower::Wizard>(100.0f, 150, 1.0f, 5);
	else
		return std::make_shared<Tower::Wizard>();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::WizardCard::Clone()
{
	auto card = std::make_shared<WizardCard>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::RangerCard::GetTower()
{
	if (m_Upgraded)
		return std::make_shared<Tower::Ranger>(30.0f, 150, 2.0f);
	else
		return std::make_shared<Tower::Ranger>();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::RangerCard::Clone()
{
	auto card = std::make_shared<RangerCard>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::GiantCard::GetTower()
{
	if (m_Upgraded)
		return std::make_shared<Tower::Giant>(300.0f, 100, 70.0f);
	else
		return std::make_shared<Tower::Giant>();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::GiantCard::Clone()
{
	auto card = std::make_shared<GiantCard>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::AlchemistCard::GetTower()
{
	if (m_Upgraded)
		return std::make_shared<Tower::Alchemist>(200.0f, 100, 1.25f);
	else
		return std::make_shared<Tower::Alchemist>();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::AlchemistCard::Clone()
{
	auto card = std::make_shared<AlchemistCard>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::BardCard::GetTower()
{
	if (m_Upgraded)
		return std::make_shared<Tower::Bard>(60.0f, 75, 1.5f);
	else
		return std::make_shared<Tower::Bard>();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::BardCard::Clone()
{
	auto card = std::make_shared<BardCard>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::ClericCard::GetTower()
{
	if (m_Upgraded)
		return std::make_shared<Tower::Cleric>(60.0f, 75, 1.25f);
	else
		return std::make_shared<Tower::Cleric>();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::ClericCard::Clone()
{
	auto card = std::make_shared<ClericCard>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::PaladinCard::GetTower()
{
	if (m_Upgraded)
		return std::make_shared<Tower::Paladin>(120.0f, 80, 8.0f);
	else
		return std::make_shared<Tower::Paladin>();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::PaladinCard::Clone()
{
	auto card = std::make_shared<PaladinCard>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::ScholarCard::GetTower()
{
	if (m_Upgraded)
		return std::make_shared<Tower::Scholar>(true);
	else
		return std::make_shared<Tower::Scholar>(false);
}

std::shared_ptr<TowerDefense::Card> TowerDefense::ScholarCard::Clone()
{
	auto card = std::make_shared<ScholarCard>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}