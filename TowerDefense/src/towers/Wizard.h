#pragma once
#include "Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Wizard : public Tower
		{
		public:
			Wizard();
			Wizard(float fireTime, int range, float damage, int numberOfMissiles);
			std::shared_ptr<Tower> Clone();

		protected:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;

		private:
			int m_NumberOfMissiles;
		};
	}
	
}