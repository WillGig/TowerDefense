#include "pch.h"
#include "CaveScene.h"

std::shared_ptr<TowerDefense::CaveScene> TowerDefense::CaveScene::GetRandomCaveEvent()
{
	int encounter = 1;// (int)(Random::GetFloat() * 4);

	if (encounter == 0)
		return std::make_shared<FountainOfYouth>();
	else if (encounter == 1)
		return std::make_shared<LiterallySatan>();
	else if (encounter == 2)
		return std::make_shared<CaveBat>();
	else
		return std::make_shared<TrolleyProblem>();
}