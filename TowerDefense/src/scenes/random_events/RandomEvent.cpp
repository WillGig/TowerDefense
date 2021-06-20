#include "pch.h"
#include "RandomEvent.h"

std::shared_ptr<TowerDefense::RandomEvent> TowerDefense::RandomEvent::GetRandomCaveEvent()
{
	int encounter = (int)(Random::GetFloat() * 10);

	if (encounter == 0)
		return std::make_shared<FountainOfYouth>();
	else if (encounter == 1)
		return std::make_shared<LiterallySatan>();
	else if (encounter == 2)
		return std::make_shared<CaveBat>();
	else if(encounter == 3)
		return std::make_shared<FrogPrince>();
	else if (encounter == 4)
		return std::make_shared<Treasure>();
	else if(encounter == 5)
		return std::make_shared<KnightsWhoSayNah>();
	else if (encounter == 6)
		return std::make_shared<WanderingSage>();
	else if (encounter == 7)
		return std::make_shared<WanderingBard>();
	else if (encounter == 8)
		return std::make_shared<WanderingCleric>();
	//else if(encounter == 9)
	//	return std::make_shared<TheBlackKnight>();
	else
		return std::make_shared<TrolleyProblem>();
}