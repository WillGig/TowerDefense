#pragma once
#include "Quirk.h"

namespace TowerDefense
{
	namespace Quirk
	{
		class WoodElf : public Quirk
		{
		public:
			WoodElf();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};
	}
}