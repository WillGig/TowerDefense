#pragma once
#include "cards/Card.h"

namespace TowerDefense
{
	class Flames : public Card
	{
	public:
		Flames();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};
}