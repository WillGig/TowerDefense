#pragma once
#include "Quirk.h"

namespace TowerDefense
{
	namespace Quirk
	{
		class Gnome : public Quirk
		{
		public:
			Gnome();
			void Apply(TowerDefense::HeroCard& h) override;
			inline std::string GetText() const override { return ""; };
			std::shared_ptr<Quirk> Clone() override;
		};
	}
}