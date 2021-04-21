#pragma once
#include "Quirk.h"

namespace TowerDefense
{
	namespace Quirk
	{
		class NearSighted : public Quirk
		{
		public:
			NearSighted();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};
	}
}