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
			std::string GetNameText(Gender gender) const override;
			std::shared_ptr<Quirk> Clone();
		};
	}
}