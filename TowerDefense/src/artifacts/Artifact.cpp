#include "pch.h"
#include "Artifact.h"

std::shared_ptr<TowerDefense::Artifact> TowerDefense::Artifact::GetRandomArtifact()
{
	int randomArtifact = (int)(Random::GetFloat() * 4);

	if (randomArtifact == 0)
		return std::make_shared<TokenOfTheMute>();
	else if (randomArtifact == 1)
		return std::make_shared<TokenOfTheArmored>();
	else if (randomArtifact == 2)
		return std::make_shared<TokenOfTheBroken>();
	else
		return std::make_shared<TokenOfTheVigilant>();
}