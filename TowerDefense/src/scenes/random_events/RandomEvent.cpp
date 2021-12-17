#include "pch.h"
#include "RandomEvent.h"

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::RandomEvent>>> TowerDefense::RandomEvent::s_Events = std::make_shared<std::vector<std::shared_ptr<TowerDefense::RandomEvent>>>();

std::shared_ptr<TowerDefense::RandomEvent> TowerDefense::RandomEvent::GetRandomEvent()
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
}

void TowerDefense::RandomEvent::CleanUp()
{
	s_Events->clear();
}