#include "pch.h"
#include "Aura.h"
#include "core/Player.h"

TowerDefense::LifeSteal::LifeSteal(int steal)
	:Aura("lifeSteal"), m_LifeSteal(steal)
{
}

void TowerDefense::LifeSteal::OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e)
{
	Player::Get().ChangeHealth(m_LifeSteal);
}