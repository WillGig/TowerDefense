#include "pch.h"
#include "Buff.h"
#include "SpeedBuff.h"
#include "towers/Tower.h"

TowerDefense::SpeedBuff::SpeedBuff(int duration, int source, float modifier)
	:Buff(duration, source), m_Modifier(modifier)
{
}

void TowerDefense::SpeedBuff::Apply(Tower::Tower& t)
{
	t.SetAttackTime(t.GetAttackTime() / m_Modifier);
}

void TowerDefense::SpeedBuff::Remove(Tower::Tower& t)
{
	t.SetAttackTime(t.GetAttackTime() * m_Modifier);
	Buff::Remove(t);
}