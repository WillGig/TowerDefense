#include "pch.h"
#include "Aura.h"
#include "core/Player.h"

TowerDefense::LifeSteal::LifeSteal(int steal)
	:Aura("lifeSteal", "Heal " + std::to_string(steal) + " health for\nevery enemy killed"), m_LifeSteal(steal)
{
}

void TowerDefense::LifeSteal::OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e)
{
	Player::Get().ChangeHealth(m_LifeSteal);
}