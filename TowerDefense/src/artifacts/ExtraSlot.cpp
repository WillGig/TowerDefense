#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::ExtraSlot::ExtraSlot()
	:Artifact("Extra Slot")
{}

void TowerDefense::ExtraSlot::OnAquire()
{
	Player::Get().AddSideBoardSlot();
}