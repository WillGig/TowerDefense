#pragma once
#include "Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Ranger : public Tower
		{
		public:
			Ranger();
			Ranger(float fireTime, int range, float damage);
			bool CanUpgrade() override;
			std::shared_ptr<Tower> Clone();

		private:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> GetPossibleUpgrades() override;
		};
	}
}