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
			void Update() override;
			bool CanUpgrade() override;
			std::shared_ptr<Tower> Clone();

			inline void SetHeal(int heal) { m_Heal = heal; }

			inline void SetShredAuraPercent(float percent) { m_ShredAuraPercent = percent; }

			inline void SetHasAttack(bool attack) { m_HasAttack = attack; }

		private:
			void Attack() override;
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> GetPossibleUpgrades() override;
			void EndRound() override;

			int m_Heal;

			float m_ShredAuraPercent;

			bool m_HasAttack;
		};
	}
}