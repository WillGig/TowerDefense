#include "pch.h"
#include "Buff.h"
#include "RangeBuff.h"
#include "towers/Tower.h"

TowerDefense::RangeBuff::RangeBuff(int duration, int source, int modifier)
	:Buff(duration, source), m_Modifier(modifier)
{}

void TowerDefense::RangeBuff::Apply(Tower::Tower& t)
{
	t.SetRange(t.GetRange() + m_Modifier);
}

void TowerDefense::RangeBuff::Remove(Tower::Tower& t)
{
	t.SetRange(t.GetRange() - m_Modifier);
	Buff::Remove(t);
}