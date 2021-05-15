#include "pch.h"
#include "Aura.h"
#include "scenes/Combat.h"

TowerDefense::DeathExplosions::DeathExplosions(int damage)
	:Aura("deathExplosions", "All enemies explode dealing\n" + std::to_string(damage) + " damage to nearby\nenemies"),
	m_Damage(damage), m_Radius(75)
{
}

void TowerDefense::DeathExplosions::OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e)
{
	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++)
	{
		auto enemy = entities->at(i);
		if (enemy->GetID() == e->GetID())
			continue;
		if (enemy->GetEntityType() == Type::ENEMY)
		{
			if (enemy->GetDistance(e->GetX(), e->GetY()) < m_Radius)
			{
				std::dynamic_pointer_cast<Enemy::Enemy>(enemy)->TakeDamage((float)m_Damage, GetID(), Tower::DamageType::MAGIC);
			}
		}
	}
	Combat::AddEntity(std::make_shared<AnimationEffect>(e->GetX(), e->GetY(), 100, 100, "fireExplosion", 7, 30));
}