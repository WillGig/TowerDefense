#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::HouseExpansionKit::HouseExpansionKit()
	:Artifact("House Expansion Kit")
{}

void TowerDefense::HouseExpansionKit::OnAquire()
{
	Player& player = Player::Get();
	player.SetMaxPopulation(player.GetMaxPopulation() + player.GetNumHouses() * 2);
}

void TowerDefense::HouseExpansionKit::OnAddHouse()
{
	Player& player = Player::Get();
	player.SetMaxPopulation(player.GetMaxPopulation() + 2);
}