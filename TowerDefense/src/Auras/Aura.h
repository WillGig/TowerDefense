#pragma once
#include "cards/Card.h"
#include "enemies/Enemy.h"

namespace TowerDefense
{
	class Aura : public Entity
	{
	public:
		Aura(const std::string name)
			:Entity(0.0f, 0.0f, 32, 32, 0.0f, name, Type::AURA), m_Name(name)
		{

		}

		inline virtual void Update() override {};
		inline virtual void OnAquire() {};
		inline virtual void OnCardPlay(std::shared_ptr<Card> c) {};
		inline virtual void OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source) {};
		inline virtual void OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e) {};

	private:
		std::string m_Name;
	};

	class LifeSteal : public Aura
	{
	public:
		LifeSteal(int steal);
		void OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e) override;

	private:
		int m_LifeSteal;
	};
}