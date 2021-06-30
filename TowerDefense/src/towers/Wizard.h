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

			inline int GetNumberOfMissiles() const { return m_NumberOfMissiles; }
			inline void SetNumberOfMissiles(int num) { m_NumberOfMissiles = num; }

			virtual std::shared_ptr<Upgrade> GetRandomTowerUpgrade(std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> exclude) override;

		protected:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;

		private:
			int m_NumberOfMissiles;
		};
	}
	
}