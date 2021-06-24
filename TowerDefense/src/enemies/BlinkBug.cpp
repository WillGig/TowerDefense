#include "pch.h"
#include "Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::BlinkBug::Update()
{
	Enemy::Update();

	for (int i = 0; i < Combat::GetRoundSpeed(); i++)
	{
		if (m_Visible)
		{
			if (m_Cast == m_CastTime)
			{
				m_Visible = false;
				m_Cast = 0;
			}
			else
				m_Cast++;
		}
		else
		{
			if (m_Cast == m_InvisibleTime)
			{
				m_Visible = true;
				m_Cast = 0;
			}
			else
				m_Cast++;
		}
	}
}