#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::Boulder::Boulder()
	:Artifact("Boulder")
{}

void TowerDefense::Boulder::OnAquire()
{
	Player::Get().ChangeResource(300, Resource::STONE);
}
