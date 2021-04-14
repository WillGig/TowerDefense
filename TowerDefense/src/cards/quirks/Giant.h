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
			std::string GetNameText(Gender gender) const;
			std::shared_ptr<Quirk> Clone();
		};
	}
}