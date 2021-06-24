#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::MapToEldorado::MapToEldorado()
	:Artifact("Map To Eldorado"), m_DaysRemaining(10)
{}

void TowerDefense::MapToEldorado::OnExplore()
{
	m_DaysRemaining--;
	if (m_DaysRemaining == 0)
		Player::Get().ChangeResource(1000, Resource::GOLD);
}