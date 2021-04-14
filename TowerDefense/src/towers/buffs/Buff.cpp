#include "pch.h"
#include "Buff.h"
#include "scenes/Combat.h"

unsigned int TowerDefense::Buff::s_ID = 0;

TowerDefense::Buff::Buff(int duration, int source)
	:m_ID(s_ID), m_Duration(duration), m_Source(source)
{
	s_ID++;
}

void TowerDefense::Buff::Update(Tower::Tower& t)
{
	m_Duration -= Combat::GetRoundSpeed();
	if (m_Duration < 1)
		Remove(t);
}

void TowerDefense::Buff::Remove(Tower::Tower& t)
{
	t.RemoveBuff(m_ID);
}