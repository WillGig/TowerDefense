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
			std::string GetNameText(Gender gender) const override;
			std::shared_ptr<Quirk> Clone();
		};
	}
}