#pragma once
#include "Quirk.h"

namespace TowerDefense
{
	namespace Quirk
	{
		class Orc : public Quirk
		{
		public:
			Orc();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};
	}
}