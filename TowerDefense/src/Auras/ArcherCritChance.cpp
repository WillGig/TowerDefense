#include "pch.h"
#include "Aura.h"
#include "cards/TowerCard.h"
#include "towers/Archer.h"
#include "towers/Ranger.h"

TowerDefense::Aura::ArcherCritChance::ArcherCritChance(float chance)
	:Aura("critChance", "Archers and Rangers\ngain " + Utils::TruncateFloat(chance*100, 1) + "% crit chance"),
	m_Chance(chance)
{}

void TowerDefense::Aura::ArcherCritChance::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetCardType() == CardType::TOWER)
	{
		auto tower = std::dynamic_pointer_cast<TowerCard>(c)->GetHeldTower();

		auto archer = std::dynamic_pointer_cast<Tower::Archer>(tower);
		auto ranger = std::dynamic_pointer_cast<Tower::Ranger>(tower);

		if (archer)
			archer->SetCritChance(archer->GetCritChance() + m_Chance);
		else if (ranger)
			ranger->SetCritChance(ranger->GetCritChance() + m_Chance);
	}
}

void TowerDefense::Aura::ArcherCritChance::Combine(std::shared_ptr<Aura> other)
{
	auto otherArcherDamage = std::dynamic_pointer_cast<ArcherCritChance>(other);
	if (otherArcherDamage)
	{
		m_Chance += otherArcherDamage->GetChance();
		m_InfoText = std::make_unique<Text>("Archers and Rangers\ngain " + Utils::TruncateFloat(m_Chance*100, 1) + "% crit chance", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}