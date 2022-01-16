#include "pch.h"
#include "Aura.h"
#include "scenes/Combat.h"

TowerDefense::Aura::DeathExplosions::DeathExplosions(int damage)
	:Aura("deathExplosions", "All enemies explode dealing\n" + std::to_string(damage) + " damage to nearby\nenemies"),
	m_Damage(damage), m_Radius(75)
{
}

void TowerDefense::Aura::DeathExplosions::OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e)
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

void TowerDefense::Aura::DeathExplosions::Combine(std::shared_ptr<Aura> other)
{
	auto otherDeathExplosions = std::dynamic_pointer_cast<DeathExplosions>(other);
	if (otherDeathExplosions)
	{
		m_Damage += otherDeathExplosions->GetDamage();
		if (otherDeathExplosions->GetRadius() > m_Radius)
			m_Radius = otherDeathExplosions->GetRadius();
		m_InfoText = std::make_unique<Text>("All enemies explode dealing\n" + std::to_string(m_Damage) + " damage to nearby\nenemies", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}