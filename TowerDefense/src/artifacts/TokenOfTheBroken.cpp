#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"
#include "cards/Lightning.h"

TowerDefense::TokenOfTheBroken::TokenOfTheBroken()
	:Artifact("TokenOfTheBroken")
{
}

void TowerDefense::TokenOfTheBroken::OnFightStart()
{
	Player::Get().GetHand()->AddCard(std::make_shared<Lightning>());
}