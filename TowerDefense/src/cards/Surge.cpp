#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::Surge::Surge()
	:Card("Surge", CardType::SKILL, 30, "surge", "surgeUpgraded")
{
}

void TowerDefense::Surge::Play()
{
	Player& player = Player::Get();
	player.ChangeEnergy(50);
	player.GetHand()->DrawCard();
	player.GetHand()->DrawCard();
	if (m_Upgraded)
		player.ChangeEnergy(20);
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Surge::Clone()
{
	auto card = std::make_shared<Surge>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}