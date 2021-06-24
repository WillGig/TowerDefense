#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::DollHouse::DollHouse()
	:Artifact("Doll House")
{}

void TowerDefense::DollHouse::OnAquire()
{
	Player::Get().AddHouse();
}