#pragma once
#include "Quirk.h"

namespace TowerDefense
{
	namespace Quirk
	{
		class Dwarf : public Quirk
		{
		public:
			Dwarf();
			void Apply(TowerDefense::HeroCard& h) override;
			inline std::string GetText() const override { return ""; };
			std::shared_ptr<Quirk> Clone() override;
		};
	}
}