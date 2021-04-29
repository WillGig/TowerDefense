#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::TokenOfTheMute::TokenOfTheMute()
	:Artifact("TokenOfTheMute")
{
}

void TowerDefense::TokenOfTheMute::OnFightStart()
{
	auto hand = Player::Get().GetHand();
	hand->DrawCard();
	hand->DrawCard();
}