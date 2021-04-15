#include "pch.h"
#include "Projectiles.h"
#include "scenes/Combat.h"

void TowerDefense::Arrow::HitEntity(std::shared_ptr<TowerDefense::Entity> e)
{
	if (e->GetEntityType() == Type::ENEMY) {
		std::shared_ptr<Enemy::Enemy> enemy = std::dynamic_pointer_cast<Enemy::Enemy>(e);
		enemy->TakeDamage(m_Damage);
	}
	Destroy();
}

void TowerDefense::MagicMissile::HitEntity(std::shared_ptr<TowerDefense::Entity> e)
{
	if (e->GetEntityType() == Type::ENEMY) {
		std::shared_ptr<Enemy::Enemy> enemy = std::dynamic_pointer_cast<Enemy::Enemy>(e);
		enemy->TakeDamage(m_Damage);
	}
	Destroy();
}

void TowerDefense::GiantRock::HitEntity(std::shared_ptr<TowerDefense::Entity> e)
{
	if (m_Health <= 0)
		return;

	for (unsigned int i = 0; i < m_HitObjects->size(); i++)
	{
		if (m_HitObjects->at(i) && m_HitObjects->at(i) == e->GetID())
			return;
	}

	if (e->GetEntityType() == Type::ENEMY) {
		std::shared_ptr<Enemy::Enemy> enemy = std::dynamic_pointer_cast<Enemy::Enemy>(e);
		enemy->TakeDamage(m_Damage);
	}

	m_HitObjects->at(m_HitObjects->size() - m_Health) = e->GetID();
	m_Health--;

	if(m_Health == 0)
		Destroy();
}

void TowerDefense::PoisonBomb::HitEntity(std::shared_ptr<TowerDefense::Entity> e)
{
	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++) {
		std::shared_ptr<Entity> e = entities->at(i);
		if (e->GetDistance(m_X, m_Y) < m_Radius)
		{
			if (e->GetEntityType() == Type::ENEMY) {
				std::shared_ptr<Enemy::Enemy> enemy = std::dynamic_pointer_cast<Enemy::Enemy>(e);
				enemy->Poison(m_Damage, m_PoisonTime);
			}
		}
	}
	Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 100, 100, "res/textures/acidExplosion.png", 7, 60));
	Destroy();
}

		