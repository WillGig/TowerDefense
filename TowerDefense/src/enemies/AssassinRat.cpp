#include "pch.h"
#include "Enemies.h"
#include "scenes/Combat.h"

void TowerDefense::Enemy::AssassinRat::Update()
{
	Enemy::Update();

	if (Combat::Paused())
		return;

	for (int i = 0; i < Combat::GetRoundSpeed(); i++)
	{
		if (m_Visible)
		{
			if (m_Cast == m_CastTime)
			{
				m_Visible = false;
				m_Running = true;
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
				m_Running = false;
				m_Cast = 0;
			}
			else
				m_Cast++;
		}
	}
}

void TowerDefense::Enemy::AssassinRat::Move()
{
	Enemy::Move();

	if(m_Running)
	{
		Enemy::Move();
		Enemy::Move();
	}
}