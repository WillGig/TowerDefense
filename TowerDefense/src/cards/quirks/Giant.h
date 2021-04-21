#pragma once
#include "Quirk.h"

namespace TowerDefense
{
	namespace Quirk
	{
		class Giant : public Quirk
		{
		public:
			Giant();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};
	}
}