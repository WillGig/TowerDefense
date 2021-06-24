#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::FruitCake::FruitCake()
	:Artifact("Fruit Cake")
{}

void TowerDefense::FruitCake::OnAquire()
{
	Player::Get().ChangeResource(300, Resource::WHEAT);
}
