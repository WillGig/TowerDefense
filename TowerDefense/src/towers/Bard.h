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
			void Update() override;
			bool CanUpgrade() override;
			std::shared_ptr<Tower> Clone();

			inline int GetRangeBuff() const { return m_RangeBuff; }
			inline void SetRangeBuff(int buff) { m_RangeBuff = buff; }

			inline float GetSlowPercentage() const { return m_SlowPercentage; }
			inline void SetSlowPercentage(float slow) { m_SlowPercentage = slow; }

			inline float GetCritBuff() const { return m_CritBuff; }
			inline void SetCritBuff(float buff) { m_CritBuff = buff; }

			inline void SetHasAttack(bool attack) { m_HasAttack = attack; }

		private:
			void Attack() override;
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> GetPossibleUpgrades() override;

			int m_RangeBuff;

			float m_SlowPercentage, m_CritBuff;

			bool m_HasAttack;
		};
	}
}