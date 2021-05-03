#pragma once
#include "Card.h"

namespace TowerDefense
{
	namespace Enemy { class Enemy; }

	class Lightning : public Card
	{
	public:
		Lightning();
		void Render() override;
		void Update() override;
		void Upgrade() override;
		bool Play() override;
		std::shared_ptr<Card> Clone() override;

	private:
		std::shared_ptr<Enemy::Enemy> GetClosestEnemy();
		std::vector<std::shared_ptr<Enemy::Enemy>> GetTargets(std::shared_ptr<Enemy::Enemy> e);
		std::shared_ptr<TowerDefense::Enemy::Enemy> GetEnemyInRange(std::shared_ptr<Enemy::Enemy> e, std::vector<std::shared_ptr<Enemy::Enemy>> exclude, float range);
		bool Contains(std::vector<std::shared_ptr<Enemy::Enemy>> list, unsigned int ID);

		float m_Damage, m_Range;
	};
}