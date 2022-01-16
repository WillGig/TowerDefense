#include "pch.h"
#include "Aura.h"
#include "towers/Tower.h"

TowerDefense::Aura::PoisonWeapons::PoisonWeapons(float poisonDamage, int poisonDuration)
	:Aura("poisonWeapons", "Towers with Physical\nDamage Apply " + Utils::TruncateFloat(poisonDamage, 1) + " Poison"),
	m_PoisonDamage(poisonDamage), m_PoisonDuration(poisonDuration)
{
}

void TowerDefense::Aura::PoisonWeapons::OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type)
{
	if (source->GetEntityType() == Type::TOWER && type == Tower::DamageType::PHYSICAL)
	{
		auto enemy = std::dynamic_pointer_cast<Enemy::Enemy>(e);
		enemy->ApplyState(std::make_shared<Enemy::Poison>(m_PoisonDuration, m_PoisonDamage, GetID(), enemy));
	}
}

void TowerDefense::Aura::PoisonWeapons::Combine(std::shared_ptr<Aura> other)
{
	auto otherPoisonWeapons = std::dynamic_pointer_cast<PoisonWeapons>(other);
	if (otherPoisonWeapons)
	{
		m_PoisonDamage += otherPoisonWeapons->GetPoisonDamage();
		if (otherPoisonWeapons->GetPoisonDuration() > m_PoisonDuration)
			m_PoisonDuration = otherPoisonWeapons->GetPoisonDuration();
		m_InfoText = std::make_unique<Text>("Towers with Physical\nDamage Apply " + Utils::TruncateFloat(m_PoisonDamage, 1) + " Poison", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}