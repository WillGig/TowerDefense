#include "pch.h"
#include "Aura.h"
#include "towers/Tower.h"

TowerDefense::StunAttacks::StunAttacks(int stunDuration, const std::string duration)
	:Aura("stunAttacks", "All Towers stun their\ntargets for " + duration + " seconds"),
	m_StunDuration(stunDuration)
{
}

void TowerDefense::StunAttacks::OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source)
{
	if (source->GetEntityType() == Type::TOWER)
		e->Stun(m_StunDuration);
}