#pragma once
#include "Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Alchemist : public Tower
		{
		public:
			Alchemist();
			Alchemist(float fireTime, int range, float damage);
			bool CanUpgrade() override;
			std::shared_ptr<Tower> Clone();

			inline int GetExplosionRadius() const { return m_ExplosionRadius; }
			inline void SetExplosionRadius(int radius) { m_ExplosionRadius = radius; }

			inline float GetGrenadeSpeed() const { return m_GrenadeSpeed; }
			inline void SetGrenadeSpeed(float speed) { m_GrenadeSpeed = speed; }

			inline float GetSlowPercent() const { return m_SlowPercent; }
			inline void SetSlowPercent(float slow) { m_SlowPercent = slow; }

			inline float GetResistanceShredPercent() const { return m_ResistanceShredPercent; }
			inline void SetResistanceShredPercent(float shred) { m_ResistanceShredPercent = shred; }

			inline int GetGoldConversion() const { return m_GoldConversion; }
			inline void SetGoldConversion(int gold) { m_GoldConversion = gold; }

		protected:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> GetPossibleUpgrades() override;

		private:
			int m_ExplosionRadius, m_GoldConversion;
			float m_GrenadeSpeed, m_SlowPercent, m_ResistanceShredPercent;
		};
	}
}