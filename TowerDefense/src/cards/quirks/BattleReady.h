#pragma once
#include "Quirk.h"

namespace TowerDefense
{
	namespace Quirk
	{
		class BattleReady : public Quirk
		{
		public:
			BattleReady();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};
	}
}