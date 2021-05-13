#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::Double::Double()
	:Card("Double", CardType::SKILL, 50, "double", "doubleUpgraded")
{
}

bool TowerDefense::Double::Play()
{
	TowerDefense::Player::Get().ChangeEnergy(TowerDefense::Player::Get().GetEnergy() - m_Cost);
	return true;
}

void TowerDefense::Double::Upgrade()
{
	Card::Upgrade();
	m_Cost = 40;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Double::Clone()
{
	auto card = std::make_shared<Double>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}