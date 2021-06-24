#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::Prince::Prince()
	:Artifact("Prince")
{}

void TowerDefense::Prince::OnFightEnd()
{
	Player::Get().ChangeResource(50, Resource::GOLD);
}