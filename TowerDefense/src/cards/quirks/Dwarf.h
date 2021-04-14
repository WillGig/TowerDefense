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
			std::string GetNameText(Gender gender) const;
			std::shared_ptr<Quirk> Clone();
		};
	}
}