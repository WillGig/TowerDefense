#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::Shrubbery::Shrubbery()
	:Artifact("Shrubbery")
{}

void TowerDefense::Shrubbery::OnRoundStart()
{
	Player::Get().ChangeEnergy(10);
}