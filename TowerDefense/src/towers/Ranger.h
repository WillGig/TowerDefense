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
			std::shared_ptr<Tower> Clone();

		protected:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;

			virtual std::shared_ptr<Upgrade> GetRandomTowerUpgrade(std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> exclude) override;
		};
	}
}