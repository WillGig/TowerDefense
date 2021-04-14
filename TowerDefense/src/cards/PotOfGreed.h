#pragma once
#include "Card.h"

namespace TowerDefense
{
	class PotOfGreed : public Card
	{
	public:
		PotOfGreed();
		void Play() override;
		std::shared_ptr<Card> Clone() override;
	};
}