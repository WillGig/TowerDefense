#pragma once
#include "Quirk.h"

namespace TowerDefense
{
	namespace Quirk
	{
		class JustLucky : public Quirk
		{
		public:
			JustLucky();
			void Apply(TowerDefense::HeroCard& h) override;
			std::string GetText() const override;
			std::shared_ptr<Quirk> Clone() override;
		};
	}
}