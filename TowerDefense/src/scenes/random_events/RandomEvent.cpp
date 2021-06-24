#include "pch.h"
#include "RandomEvent.h"

<<<<<<< HEAD
std::unique_ptr<std::vector<std::shared_ptr<TowerDefense::RandomEvent>>> TowerDefense::RandomEvent::s_Events = std::make_unique<std::vector<std::shared_ptr<TowerDefense::RandomEvent>>>();

std::shared_ptr<TowerDefense::RandomEvent> TowerDefense::RandomEvent::GetRandomCaveEvent()
{

	if (s_Events->size() == 0)
	{
		s_Events->push_back(std::make_shared<FountainOfYouth>());
		s_Events->push_back(std::make_shared<LiterallySatan>());
		s_Events->push_back(std::make_shared<CaveBat>());
		s_Events->push_back(std::make_shared<FrogPrince>());
		s_Events->push_back(std::make_shared<Treasure>());
		s_Events->push_back(std::make_shared<KnightsWhoSayNah>());
		s_Events->push_back(std::make_shared<WanderingSage>());
		s_Events->push_back(std::make_shared<WanderingBard>());
		s_Events->push_back(std::make_shared<WanderingCleric>());
		s_Events->push_back(std::make_shared<TheBlackKnight>());
		s_Events->push_back(std::make_shared<TrolleyProblem>());
	}

	int randomEvent = (int)(Random::GetFloat() * s_Events->size());
	auto e = s_Events->at(randomEvent);
	s_Events->erase(s_Events->begin() + randomEvent);
	return e;
=======
std::shared_ptr<TowerDefense::RandomEvent> TowerDefense::RandomEvent::GetRandomCaveEvent()
{
	int encounter = (int)(Random::GetFloat() * 11);

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
	else if(encounter == 9)
		return std::make_shared<TheBlackKnight>();
	else
		return std::make_shared<TrolleyProblem>();
>>>>>>> 190f5d53eb452ef28f88bc5a3bbd65d3d1be5c32
}