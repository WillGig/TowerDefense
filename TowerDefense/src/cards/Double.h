#pragma once
#include "Card.h"

namespace TowerDefense
{
	class Double : public Card {
	public:
		Double();
		bool Play() override;
		void Upgrade() override;
		std::shared_ptr<Card> Clone() override;
	};
}