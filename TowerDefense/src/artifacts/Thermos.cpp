#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::Thermos::Thermos()
	:Artifact("Thermos")
{}

void TowerDefense::Thermos::OnFightStart()
{
	Player::Get().ChangeEnergy(50);
}