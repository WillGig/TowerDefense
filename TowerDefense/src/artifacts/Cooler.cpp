#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::Cooler::Cooler()
	:Artifact("Cooler"), m_EndEnergy(-1)
{}

TowerDefense::Cooler::Cooler(int endEnergy)
	: Artifact("Cooler"), m_EndEnergy(endEnergy)
{}

void TowerDefense::Cooler::OnFightStart()
{
	if(m_EndEnergy != -1)
		Player::Get().SetEnergy(m_EndEnergy);
}

void TowerDefense::Cooler::OnFightEnd()
{
	m_EndEnergy = Player::Get().GetEnergy();
}