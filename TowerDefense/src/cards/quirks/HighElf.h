#pragma once
#include "Quirk.h"

namespace TowerDefense
{
	namespace Quirk
	{
		class HighElf : public Quirk
		{
		public:
			HighElf();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};
	}
}