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
			bool CanUpgrade() override;
			std::shared_ptr<Tower> Clone();

			inline void SetHeal(int heal) { m_Heal = heal; }

		private:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			void EndRound() override;

			int m_Heal;
		};
	}
}