#pragma once
#include "Enemy.h"

namespace TowerDefense
{
	class EnemyInfo : public Entity
	{
	public:
		EnemyInfo(float x, float y, std::shared_ptr<Enemy::Enemy> e);
		void Render() override;
		void Update() override;

		void SetX(float x) override;
		void SetY(float y) override;

		inline bool Dragging() { return m_Dragging; }

	private:
		void UpdateStatsText();

		bool m_Dragging;
		float m_PreviousMouseX, m_PreviousMouseY, m_EnemyHP, m_EnemySpeed, m_EnemyArmor, m_EnemyMagicResistance;

		std::unique_ptr<Text> m_Name, m_Stats, m_StatsNumbers;

		std::shared_ptr<Enemy::Enemy> m_Enemy;
	};
}