#include "pch.h"
#include "Aura.h"
#include "towers/Tower.h"

TowerDefense::Aura::StunAttacks::StunAttacks(int stunDuration)
	:Aura("stunAttacks", "All Towers stun their\ntargets for " + Utils::TruncateFloat((float)stunDuration/60.0f, 1) + " seconds"),
	m_StunDuration(stunDuration)
{
}

void TowerDefense::Aura::StunAttacks::OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type)
{
	if (source->GetEntityType() == Type::TOWER && type != Tower::DamageType::POISON)
		std::dynamic_pointer_cast<Enemy::Enemy>(e)->ApplyState(std::make_shared<Enemy::Stun>(m_StunDuration));
}

void TowerDefense::Aura::StunAttacks::Combine(std::shared_ptr<Aura> other)
{
	auto otherStunAttacks = std::dynamic_pointer_cast<StunAttacks>(other);
	if (otherStunAttacks)
	{
		m_StunDuration += otherStunAttacks->GetStunDuration();
		m_InfoText = std::make_unique<Text>("All Towers stun their\ntargets for " + Utils::TruncateFloat((float)m_StunDuration / 60.0f, 1) + " seconds", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

const std::string TowerDefense::Aura::StunAttacks::GetSaveData() const
{
	return "Stun Attacks\n" + std::to_string(m_StunDuration);
}