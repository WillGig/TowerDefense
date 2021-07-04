#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::MagicalGenerator::MagicalGenerator()
	:Artifact("Magical Generator")
{}

void TowerDefense::MagicalGenerator::OnFightStart()
{
	Player::Get().ChangeEnergy(100);
}