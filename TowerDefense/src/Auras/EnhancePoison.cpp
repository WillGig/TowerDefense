#include "pch.h"
#include "Aura.h"
#include "towers/Tower.h"

TowerDefense::Aura::EnhancePoison::EnhancePoison(float extraDamage)
	:Aura("enhancePoison", "All poisons deal " + Utils::TruncateFloat(extraDamage*2, 1) + "\nextra damage per second"), m_ExtraDamage(extraDamage)
{
}

void TowerDefense::Aura::EnhancePoison::OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type)
{
	if (type == Tower::DamageType::POISON)
		e->TakeDamage(m_ExtraDamage, GetID(), Tower::DamageType::TRUE);
}

void TowerDefense::Aura::EnhancePoison::Combine(std::shared_ptr<Aura> other)
{
	auto otherEnhancePoison = std::dynamic_pointer_cast<EnhancePoison>(other);
	if (otherEnhancePoison)
	{
		m_ExtraDamage += otherEnhancePoison->GetExtraDamage();
		m_InfoText = std::make_unique<Text>("All poisons deal " + Utils::TruncateFloat(m_ExtraDamage * 2, 1) + "\nextra damage per second", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

const std::string TowerDefense::Aura::EnhancePoison::GetSaveData() const
{
	return "Enhance Poison\n" + Utils::TruncateFloat(m_ExtraDamage, 1);
}