#pragma once
#include "Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Giant : public Tower
		{
		public:
			Giant();
			Giant(float fireTime, int range, float damage);
			bool CanUpgrade() override;
			std::shared_ptr<Tower> Clone();

		protected:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
		};
	}
}