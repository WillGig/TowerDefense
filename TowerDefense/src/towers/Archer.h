#pragma once
#include "Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Archer : public Tower
		{
		public:
			Archer();
			Archer(float fireTime, int range, float damage);
			std::shared_ptr<Tower> Clone();

		protected:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
		};
	}
}