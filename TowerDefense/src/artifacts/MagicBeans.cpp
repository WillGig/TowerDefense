#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::MagicBeans::MagicBeans()
	:Artifact("Magic Beans")
{}

void TowerDefense::MagicBeans::OnAquire()
{
	Player::Get().ChangeResource(300, Resource::WOOD);
}
