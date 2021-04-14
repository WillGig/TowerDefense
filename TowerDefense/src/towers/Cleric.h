#pragma once
#include "Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Cleric : public Tower
		{
		public:
			Cleric();
			Cleric(float fireTime, int range, float buff);
			std::shared_ptr<Tower> Clone();

		protected:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;

		private:
			float m_DamageBuff;
		};
	}
}