#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::Center::Center()
	:Card("Center", CardType::SKILL, 10, "center", "centerUpgraded")
{
}

void TowerDefense::Center::Play()
{
	Player::Get().ChangeEnergy(50);
	if (m_Upgraded)
		Player::Get().ChangeEnergy(20);
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Center::Clone()
{
	auto card = std::make_shared<Center>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}