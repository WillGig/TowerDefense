#pragma once
#include "Tower.h"
#include "AnimalCompanion.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Ranger : public Tower
		{
		public:
			Ranger();
			Ranger(float fireTime, int range, float damage);
			void Update() override;
			void Render() override;
			bool CanUpgrade() override;
			std::shared_ptr<Tower> Clone();

			//Number of enemies that can be hit by each shot
			inline int GetPierce() const { return m_Pierce; }
			inline void SetPierce(int num) { m_Pierce = num; }

			inline void SetCompanion(std::shared_ptr<AnimalCompanion> companion) { m_Companion = companion; }

		private:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> GetPossibleUpgrades() override;

			int m_Pierce;

			std::shared_ptr<AnimalCompanion> m_Companion;
		};
	}
}