#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::TokenOfTheArmored::TokenOfTheArmored()
	:Artifact("Token Of The Armored")
{
}

void TowerDefense::TokenOfTheArmored::OnFightEnd()
{
	Player::Get().ChangeHealth(3);
}