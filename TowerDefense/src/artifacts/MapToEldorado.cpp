#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::MapToEldorado::MapToEldorado()
	:Artifact("Map To Eldorado"), m_DaysRemaining(10)
{}

TowerDefense::MapToEldorado::MapToEldorado(int daysRemaining)
	: Artifact("Map To Eldorado"), m_DaysRemaining(daysRemaining)
{}

void TowerDefense::MapToEldorado::OnExplore()
{
	m_DaysRemaining--;
	if (m_DaysRemaining == 0)
		Player::Get().ChangeResource(1000, Resource::GOLD);
}