#pragma once
#include "cards/Card.h"
#include "cards/HeroCard.h"
#include <string>

namespace TowerDefense
{
	class Upgrade : public Card
	{
	public:
		Upgrade(const std::string& name, const std::string& image)
			:Card(name, CardType::SKILL, 0, image, image)
		{
		}
		virtual void UpgradeHero(HeroCard& hero) = 0;
		inline void Play() override {};
		inline std::shared_ptr<Card> Clone() { return nullptr; }
	};
}