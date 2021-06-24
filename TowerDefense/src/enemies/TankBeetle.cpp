#include "pch.h"
#include "Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::TankBeetle::Update()
{
	Enemy::Update();

	for (int i = 0; i < Combat::GetRoundSpeed(); i++)
	{
		if (m_Switch == m_SwitchTime)
		{
			if (m_Armor == 200)
			{
				m_Armor = 0;
				m_MagicResistance = 200;
			}
			else
			{
				m_Armor = 200;
				m_MagicResistance = 0;
			}
			m_Switch = 0;
		}
		else
			m_Switch++;
	}
}