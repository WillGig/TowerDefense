#pragma once
#include "cards/Card.h"

namespace TowerDefense
{
	class Flames : public Card
	{
	public:
		Flames();
		void Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Frog : public Card
	{
	public:
		Frog();
		void Play() override;
		std::shared_ptr<Card> Clone() override;
	};
}