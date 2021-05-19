#include "pch.h"
#include "Enemies.h"

void TowerDefense::Enemy::JumpingOoze::Move()
{
	if (m_JumpCoolDown == 0)
	{
		if (m_JumpFrame == 0)
		{
			m_JumpFrame = m_JumpTime;
			m_JumpCoolDown = m_TimeBetweenJumps;
		}
		else
			m_JumpFrame--;
	}
	else
		m_JumpCoolDown--;
		
	Enemy::Move();

	if (m_JumpFrame != 0 && m_JumpCoolDown == 0)
	{
		Enemy::Move();
		Enemy::Move();
	}
		
}