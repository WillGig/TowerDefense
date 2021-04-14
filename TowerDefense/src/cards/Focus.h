#pragma once
#include "Card.h"

namespace TowerDefense
{
	class Focus : public Card {
	public:
		Focus(bool exhausts);
		void Play() override;
		std::shared_ptr<Card> Clone() override;
	};
}