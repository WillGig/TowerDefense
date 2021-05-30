#include "pch.h"
#include "Artifact.h"

std::shared_ptr<TowerDefense::Artifact> TowerDefense::Artifact::GetRandomArtifact()
{
	int randomArtifact = (int)(Random::GetFloat() * 7);

	if (randomArtifact == 0)
		return std::make_shared<TokenOfTheMute>();
	else if (randomArtifact == 1)
		return std::make_shared<TokenOfTheArmored>();
	else if (randomArtifact == 2)
		return std::make_shared<TokenOfTheBroken>();
	else if(randomArtifact == 3)
		return std::make_shared<TokenOfTheVigilant>();
	else if (randomArtifact == 4)
		return std::make_shared<LuckyAxe>();
	else if (randomArtifact == 5)
		return std::make_shared<LuckyPickaxe>();
	else
		return std::make_shared<LuckySythe>();
}