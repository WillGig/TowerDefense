#pragma once
#include "Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Bard : public Tower
		{
		public:
			Bard();
			Bard(float fireTime, int range, float buff);
			bool CanUpgrade() override;
			std::shared_ptr<Tower> Clone();

		protected:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
		};
	}
}