#pragma once
#include "Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Paladin : public Tower
		{
		public:
			Paladin();
			Paladin(float fireTime, int range, float damage);
			void Update() override;
			bool CanUpgrade() override;
			std::shared_ptr<Tower> Clone();

			inline void SetSpeed(float speed) { m_Speed = speed; }

		private:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> GetPossibleUpgrades() override;
			std::shared_ptr<TowerDefense::Entity> FindTarget() override;
			void Attack() override;
			void Move();

			float m_Speed, m_XDisplacement, m_YDisplacement;
		};
	}
}