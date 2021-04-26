#include "pch.h"
#include "CaveScene.h"

std::shared_ptr<TowerDefense::CaveScene> TowerDefense::CaveScene::GetRandomCaveEvent()
{
	int encounter = (int)(Random::GetFloat() * 3);

	if (encounter == 0)
		return std::make_shared<FountainOfYouth>();
	else if (encounter == 1)
		return std::make_shared<LiterallySatan>();
	else if (encounter == 2)
		return std::make_shared<TrolleyProblem>();
	else
		return std::make_shared<CaveBat>();
}