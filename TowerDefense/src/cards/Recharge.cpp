#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::Recharge::Recharge()
	:Card("Recharge", CardType::SKILL, 20, "recharge", "rechargeUpgraded")
{
}

bool TowerDefense::Recharge::Play()
{
	Player& player = Player::Get();
	player.ChangeEnergy(30);
	player.GetHand()->DrawCard();
	if (m_Upgraded)
		player.GetHand()->DrawCard();

	return true;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Recharge::Clone()
{
	auto card = std::make_shared<Recharge>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}