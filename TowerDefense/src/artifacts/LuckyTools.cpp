#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::LuckyAxe::LuckyAxe()
	:Artifact("Lucky Axe")
{}

void TowerDefense::LuckyAxe::OnAquire()
{
	Player::Get().SetResourceGatherRate(Player::Get().GetResourceGatherRate(Resource::WOOD) + 50, Resource::WOOD);
}

TowerDefense::LuckyPickaxe::LuckyPickaxe()
	:Artifact("Lucky Pickaxe")
{}

void TowerDefense::LuckyPickaxe::OnAquire()
{
	Player::Get().SetResourceGatherRate(Player::Get().GetResourceGatherRate(Resource::STONE) + 50, Resource::STONE);
}

TowerDefense::LuckySythe::LuckySythe()
	:Artifact("Lucky Sythe")
{}

void TowerDefense::LuckySythe::OnAquire()
{
	Player::Get().SetResourceGatherRate(Player::Get().GetResourceGatherRate(Resource::WHEAT) + 50, Resource::WHEAT);
}