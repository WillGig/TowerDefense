#pragma once
#include "Card.h"

namespace TowerDefense
{
	class Focus : public Card {
	public:
		Focus(bool exhausts);
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};
}