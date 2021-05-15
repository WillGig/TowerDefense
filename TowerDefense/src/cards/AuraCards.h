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

	class Envenom : public Card
	{
	public:
		Envenom();
		void Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class StunningStrikes : public Card
	{
	public:
		StunningStrikes();
		void Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class TheFloorIsLava : public Card
	{
	public:
		TheFloorIsLava();
		void Play() override;
		std::shared_ptr<Card> Clone() override;
	};
}