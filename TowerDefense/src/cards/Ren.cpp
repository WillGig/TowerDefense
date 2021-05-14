#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"

TowerDefense::Ren::Ren()
	:Card("Ren", CardType::SKILL, 100, "ren", "renUpgraded")
{
}

void TowerDefense::Ren::Upgrade()
{
	Card::Upgrade();
	m_Cost = 80;
}

void TowerDefense::Ren::Play()
{
	Player::Get().ChangeEnergy(200);
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Ren::Clone()
{
	auto card = std::make_shared<Ren>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}