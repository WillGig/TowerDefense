#pragma once
#include "Quirk.h"

namespace TowerDefense
{
	namespace Quirk
	{
		class Human : public Quirk
		{
		public:
			Human();
			void Apply(TowerDefense::HeroCard& h) override;
			std::string GetNameText(Gender gender) const;
			std::shared_ptr<Quirk> Clone();
		};
	}
}