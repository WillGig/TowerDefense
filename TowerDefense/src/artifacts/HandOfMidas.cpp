#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::HandOfMidas::HandOfMidas()
	:Artifact("Hand of Midas")
{}

void TowerDefense::HandOfMidas::OnAquire()
{
	Player& player = Player::Get();
	player.ChangeResource(player.GetResource(Resource::WOOD) + player.GetResource(Resource::STONE) + player.GetResource(Resource::WHEAT), Resource::GOLD);
	player.ChangeResource(player.GetResource(Resource::GOLD), Resource::GOLD);
	player.SetResource(0, Resource::WOOD);
	player.SetResource(0, Resource::STONE);
	player.SetResource(0, Resource::WHEAT);
}