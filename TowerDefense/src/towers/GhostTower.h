#pragma once
#include "Archer.h"
#include "Wizard.h"

namespace TowerDefense
{
	namespace Tower
	{
		class GhostArcher : public Archer
		{
		public:
			GhostArcher(float damage, int multishot, float critChance, int time, unsigned int master);
			void Update() override;

		private:
			int m_TimeUntilDeath;				
			float m_DamageGivenToMaster;
			std::shared_ptr<Wizard> m_Master;
		};
	}
}