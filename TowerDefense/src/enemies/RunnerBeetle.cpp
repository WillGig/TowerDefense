#include "pch.h"
#include "Enemies.h"

void TowerDefense::Enemy::RunnerBeetle::Move()
{
	Enemy::Move();

	if (m_Cast == m_CastTime)
	{
		if (m_Run == m_RunTime)
		{
			m_Run = 0;
			m_Cast = 0;
		}
		else
			m_Run++;
	}
	else
		m_Cast++;

	if (m_Cast == m_CastTime)
	{
		Enemy::Move();
		Enemy::Move();
		Enemy::Move();
	}
}