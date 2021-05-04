#include "pch.h"
#include "Focus.h"
#include "core/Player.h"

TowerDefense::Focus::Focus(bool exhausts)
	:Card("Focus", CardType::SKILL, 0, exhausts ? "focusExhausts" : "focus", exhausts ? "focusExhaustsUpgraded" : "focusUpgraded")
{
	m_Exhausts = exhausts;
	if(exhausts)
		AddInfoCard(std::make_shared<InfoTile>("exhaustInfo"));
}

bool TowerDefense::Focus::Play()
{
	if (m_Upgraded)
		TowerDefense::Player::Get().ChangeEnergy(30);
	else
		TowerDefense::Player::Get().ChangeEnergy(20);
	return true;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Focus::Clone()
{
	auto card = std::make_shared<Focus>(m_Exhausts);
	if (m_Upgraded)
		card->Upgrade();
	return card;
}