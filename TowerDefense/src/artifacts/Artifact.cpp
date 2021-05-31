#include "pch.h"
#include "Artifact.h"

std::unique_ptr<std::vector<std::shared_ptr<TowerDefense::Artifact>>> TowerDefense::Artifact::s_Artifacts = std::make_unique<std::vector<std::shared_ptr<TowerDefense::Artifact>>>();

std::shared_ptr<TowerDefense::Artifact> TowerDefense::Artifact::GetRandomArtifact()
{
	if (s_Artifacts->size() == 0)
	{
		s_Artifacts->push_back(std::make_shared<TokenOfTheMute>());
		s_Artifacts->push_back(std::make_shared<TokenOfTheArmored>());
		s_Artifacts->push_back(std::make_shared<TokenOfTheBroken>());
		s_Artifacts->push_back(std::make_shared<TokenOfTheVigilant>());
		s_Artifacts->push_back(std::make_shared<LuckyAxe>());
		s_Artifacts->push_back(std::make_shared<LuckyPickaxe>());
		s_Artifacts->push_back(std::make_shared<LuckySythe>());
		s_Artifacts->push_back(std::make_shared<Boulder>());
		s_Artifacts->push_back(std::make_shared<MagicBeans>());
		s_Artifacts->push_back(std::make_shared<FruitCake>());
		s_Artifacts->push_back(std::make_shared<DollHouse>());
		s_Artifacts->push_back(std::make_shared<ToyDolls>());
		s_Artifacts->push_back(std::make_shared<HandOfMidas>());
		s_Artifacts->push_back(std::make_shared<HouseExpansionKit>());
		s_Artifacts->push_back(std::make_shared<Thermos>());
		s_Artifacts->push_back(std::make_shared<Cooler>());
	}

	int randomArtifact = (int)(Random::GetFloat() * s_Artifacts->size());
	auto a = s_Artifacts->at(randomArtifact);
	s_Artifacts->erase(s_Artifacts->begin() + randomArtifact);
	return a;
}

void TowerDefense::Artifact::CleanUp()
{
	s_Artifacts->clear();
}