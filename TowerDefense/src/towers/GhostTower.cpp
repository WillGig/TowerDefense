#include "pch.h"
#include "GhostTower.h"
#include "scenes/Combat.h"

TowerDefense::Tower::GhostArcher::GhostArcher(float damage, int multishot, float critChance, int time, unsigned int master)
	:Archer(), m_TimeUntilDeath(time), m_DamageGivenToMaster(0)
{
	m_PhysicalDamage = damage;
	m_CritChance = critChance;
	SetNumberOfArrows(multishot);

	m_Visible = false;

	m_Master = std::dynamic_pointer_cast<Wizard>(Combat::GetEntity(master));
}

void TowerDefense::Tower::GhostArcher::Update()
{
	Archer::Update();

	m_Master->AddDamageDealt(GetDamageDealt() - m_DamageGivenToMaster);
	m_DamageGivenToMaster = GetDamageDealt();

	m_TimeUntilDeath -= Combat::GetRoundSpeed();

	if (m_TimeUntilDeath < 1)
		Destroy();
}