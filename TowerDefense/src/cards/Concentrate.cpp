#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::Concentrate::Concentrate()
	:Card("Concentrate", CardType::SKILL, 20, "concentrate", "concentrateUpgraded")
{
}

void TowerDefense::Concentrate::Play()
{
	Player& player = Player::Get();
	player.ChangeEnergy(70);
	if (m_Upgraded)
		player.ChangeEnergy(30);
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Concentrate::Clone()
{
	auto card = std::make_shared<Concentrate>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}