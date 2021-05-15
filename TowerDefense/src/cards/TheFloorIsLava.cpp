#include "pch.h"
#include "AuraCards.h"
#include "scenes/Combat.h"

TowerDefense::TheFloorIsLava::TheFloorIsLava()
	:Card("The Floor is Lava", CardType::AURA, 50, "theFloorIsLava", "theFloorIsLavaUpgraded")
{
	m_Exhausts = true;
	AddInfoCard(std::make_shared<InfoTile>("auraInfo"));
}

void TowerDefense::TheFloorIsLava::Play()
{
	if (m_Upgraded)
		Combat::AddAura(std::make_shared<ConstantDamage>(2.0f, 120, "2 Damage every 2\nSeconds"));
	else
		Combat::AddAura(std::make_shared<ConstantDamage>(1.0f, 120, "1 Damage every 2\nSeconds"));
}

std::shared_ptr<TowerDefense::Card> TowerDefense::TheFloorIsLava::Clone()
{
	auto card = std::make_shared<TheFloorIsLava>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}