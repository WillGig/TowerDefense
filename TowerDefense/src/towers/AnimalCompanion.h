#pragma once
#include "Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class AnimalCompanion : public Tower
		{
		public:
			AnimalCompanion(float damage, float attackSpeed, int range, float speed, const std::string& name, std::shared_ptr<Tower> master);
			void Update() override;

			inline virtual std::shared_ptr<Tower> Clone() { return nullptr; }
			inline virtual bool CanUpgrade() { return false; }

		private:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			void Move();
			void FindGoal();
			float GetDirection(std::shared_ptr<TowerDefense::Entity> e);

			float m_GoalX, m_GoalY, m_Speed;

			float m_GoalDirection, m_CurrentDirection;

			std::shared_ptr<Tower> m_Master;
		};
	}
}
