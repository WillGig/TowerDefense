#pragma once
#include "Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Paladin : public Tower
		{
		public:
			Paladin();
			Paladin(float fireTime, int range, float damage);
			void Update() override;
			void Render() override;
			bool CanUpgrade() override;
			std::shared_ptr<Tower> Clone();

			inline void SetSpeed(float speed) { m_Speed = speed; }

			inline void SetDamageRadius(float radius) { m_DamageRadius = radius; }

			inline void SetInspiring(bool inspiring) { m_Inspiring = inspiring; }

		private:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> GetPossibleUpgrades() override;
			std::shared_ptr<TowerDefense::Entity> FindTarget() override;
			void Attack() override;
			void Move();

			int m_CircleTimer;

			bool m_Inspiring;

			float m_Speed, m_XDisplacement, m_YDisplacement, m_DamageRadius;

			Circle m_DamageRadiusCircle;
		};
	}
}