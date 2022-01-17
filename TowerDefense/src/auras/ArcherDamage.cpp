#include "pch.h"
#include "Aura.h"
#include "cards/TowerCard.h"
#include "towers/Archer.h"
#include "towers/Ranger.h"

TowerDefense::Aura::ArcherDamage::ArcherDamage(float damage)
	:Aura("archerDamage", "Archers and Rangers\ndeal " + Utils::TruncateFloat(damage, 1) + " extra damage"),
	m_Damage(damage)
{}

void TowerDefense::Aura::ArcherDamage::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetCardType() == CardType::TOWER)
	{
		auto tower = std::dynamic_pointer_cast<TowerCard>(c)->GetHeldTower();

		auto archer = std::dynamic_pointer_cast<Tower::Archer>(tower);
		auto ranger = std::dynamic_pointer_cast<Tower::Ranger>(tower);

		if (archer)
			archer->SetDamage(archer->GetDamage(Tower::DamageType::PHYSICAL) + m_Damage, Tower::DamageType::PHYSICAL);
		else if (ranger)
			ranger->SetDamage(ranger->GetDamage(Tower::DamageType::PHYSICAL) + m_Damage, Tower::DamageType::PHYSICAL);
	}
}

void TowerDefense::Aura::ArcherDamage::Combine(std::shared_ptr<Aura> other)
{
	auto otherArcherDamage = std::dynamic_pointer_cast<ArcherDamage>(other);
	if (otherArcherDamage)
	{
		m_Damage += otherArcherDamage->GetDamage();
		m_InfoText = std::make_unique<Text>("Archers and Rangers\ndeal " + Utils::TruncateFloat(m_Damage, 1) + " extra damage", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}