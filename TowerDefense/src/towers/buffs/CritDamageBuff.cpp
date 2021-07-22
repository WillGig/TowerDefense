#include "pch.h"
#include "Buff.h"
#include "CritDamageBuff.h"
#include "towers/Tower.h"

TowerDefense::CritDamageBuff::CritDamageBuff(int duration, int source, float modifier)
	:Buff(duration, source), m_Modifier(modifier)
{}

void TowerDefense::CritDamageBuff::Apply(Tower::Tower& t)
{
	t.SetCritMultiplier(t.GetCritMultiplier() + m_Modifier);
}

void TowerDefense::CritDamageBuff::Remove(Tower::Tower& t)
{
	t.SetCritMultiplier(t.GetCritMultiplier() - m_Modifier);
	Buff::Remove(t);
}