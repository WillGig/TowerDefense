#pragma once
#include "Quirk.h"

namespace TowerDefense
{
	namespace Quirk
	{
		class Veteran : public Quirk
		{
		public:
			Veteran();
			void Apply(TowerDefense::HeroCard& h) override;
			std::string GetNameText(Gender gender) const override;
			std::shared_ptr<Quirk> Clone();
		};
	}
}