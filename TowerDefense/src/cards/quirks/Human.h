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
			inline std::string GetText() const override { return ""; };
			std::shared_ptr<Quirk> Clone() override;
		};
	}
}