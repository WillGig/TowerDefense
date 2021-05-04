#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"
#include "cards/Lightning.h"

TowerDefense::TokenOfTheBroken::TokenOfTheBroken()
	:Artifact("Token Of The Broken")
{
}

void TowerDefense::TokenOfTheBroken::OnFightStart()
{
	Player::Get().GetHand()->AddCard(std::make_shared<Lightning>());
}