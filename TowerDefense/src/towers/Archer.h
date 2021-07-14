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
			bool CanUpgrade() override;
			std::shared_ptr<Tower> Clone();

			//Number of arrows per fire in a cone
			inline int GetNumberOfArrows() const { return m_NumberOfArrows; }
			inline void SetNumberOfArrows(int num) { m_NumberOfArrows = num; }
			
			//Number of enemies that can be hit by each shot
			inline int GetPierce() const { return m_Pierce; }
			inline void SetPierce(int num) { m_Pierce = num; }

		private:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> GetPossibleUpgrades() override;

			int m_NumberOfArrows, m_Pierce;
		};
	}
}