#pragma once
#include "Card.h"

namespace TowerDefense
{
	class LifeAura : public Card
	{
	public:
		LifeAura();
		void Play() override;
		std::shared_ptr<Card> Clone() override;
	};
}