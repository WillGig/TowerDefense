#include "pch.h"
#include "Buff.h"
#include "DamageBuff.h"
#include "towers/Tower.h"

TowerDefense::DamageBuff::DamageBuff(int duration, int source, Tower::DamageType type, float modifier)
	:Buff(duration, source), m_Type(type), m_Modifier(modifier)
{
}

void TowerDefense::DamageBuff::Apply(Tower::Tower& t)
{
	t.SetDamageModifier(t.GetDamageModifier(m_Type) + m_Modifier, m_Type);
}

void TowerDefense::DamageBuff::Remove(Tower::Tower& t)
{
	t.SetDamageModifier(t.GetDamageModifier(m_Type) - m_Modifier, m_Type);
	Buff::Remove(t);
}