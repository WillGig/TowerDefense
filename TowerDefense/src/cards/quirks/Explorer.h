#pragma once
#include "Quirk.h"

namespace TowerDefense
{
	namespace Quirk
	{
		class Explorer : public Quirk
		{
		public:
			Explorer();
			void OnPlay() override;
			std::string GetNameText(Gender gender) const override;
			std::shared_ptr<Quirk> Clone();
		};
	}
}