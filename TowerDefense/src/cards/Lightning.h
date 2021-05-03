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

		float m_Damage, m_Range;
	};
}