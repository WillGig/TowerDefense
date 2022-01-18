#include "pch.h"
#include "Aura.h"
#include "cards/TowerCard.h"
#include "towers/Alchemist.h"

TowerDefense::Aura::AlchemistDamage::AlchemistDamage(float damage)
	:Aura("damageUp", "Alchemists\ndeal " + Utils::TruncateFloat(damage, 1) + " extra damage"),
	m_Damage(damage)
{}

void TowerDefense::Aura::AlchemistDamage::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetCardType() == CardType::TOWER)
	{
		auto tower = std::dynamic_pointer_cast<TowerCard>(c)->GetHeldTower();

		auto alchemist = std::dynamic_pointer_cast<Tower::Alchemist>(tower);

		if (alchemist)
			alchemist->SetDamage(alchemist->GetDamage(Tower::DamageType::MAGIC) + m_Damage, Tower::DamageType::MAGIC);
	}
}

void TowerDefense::Aura::AlchemistDamage::Combine(std::shared_ptr<Aura> other)
{
	auto otherAlchemistDamage = std::dynamic_pointer_cast<AlchemistDamage>(other);
	if (otherAlchemistDamage)
	{
		m_Damage += otherAlchemistDamage->GetDamage();
		m_InfoText = std::make_unique<Text>("Alchemists deal " + Utils::TruncateFloat(m_Damage, 1) + " extra damage", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}