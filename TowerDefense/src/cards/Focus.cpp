#include "pch.h"
#include "Focus.h"
#include "core/Player.h"

TowerDefense::Focus::Focus(bool exhausts)
	:Card("Focus", 0, exhausts ? "res/textures/focusExhausts.png" : "res/textures/focus.png", exhausts ? "res/textures/focusExhaustsUpgraded.png" : "res/textures/focusUpgraded.png")
{
	m_Exhausts = exhausts;
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