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

			inline int GetNumberOfArrows() const { return m_NumberOfArrows; }
			inline void SetNumberOfArrows(int num) { m_NumberOfArrows = num; }

		private:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> GetPossibleUpgrades() override;

			int m_NumberOfArrows;
		};
	}
}