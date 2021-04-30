#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::TokenOfTheArmored::TokenOfTheArmored()
	:Artifact("TokenOfTheArmored")
{
}

void TowerDefense::TokenOfTheArmored::OnFightEnd()
{
	Player::Get().ChangeHealth(3);
}