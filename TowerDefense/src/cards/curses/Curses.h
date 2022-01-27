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

	class Infection : public Card
	{
	public:
		Infection();
		void Play() override;
		void Upgrade() override;
		void OnUnplayed() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Hex : public Card
	{
	public:
		Hex();
		void Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Sludge : public Card
	{
	public:
		Sludge();
		void Play() override;
		void Upgrade() override;
		std::shared_ptr<Card> Clone() override;
	};
}