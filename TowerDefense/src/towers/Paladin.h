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
			std::shared_ptr<Tower> Clone();

		protected:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
		};
	}
}