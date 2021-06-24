#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::ExplorersHat::ExplorersHat()
	:Artifact("Explorers Hat")
{}

void TowerDefense::ExplorersHat::OnAquire()
{
	Player::Get().SetResourceGatherRate(Player::Get().GetResourceGatherRate(Resource::EXPLORE) + 50, Resource::EXPLORE);
}