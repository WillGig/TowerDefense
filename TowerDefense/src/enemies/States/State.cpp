#include "pch.h"
#include "State.h"
#include "scenes/Combat.h"

TowerDefense::Enemy::State::State(int time, StateType type)
	:m_TimeRemaining(time), m_Active(true), m_Type(type)
{}

void TowerDefense::Enemy::State::Update()
{
	m_TimeRemaining -= Combat::GetRoundSpeed();
	if (m_TimeRemaining < 1)
		m_Active = false;
}

TowerDefense::Enemy::Slow::Slow(int time, float slowPercent)
	:State(time, StateType::SLOW), m_SlowPercent(slowPercent)
{}

void TowerDefense::Enemy::Slow::OnApply(Enemy& e)
{
	e.SetSpeed(e.GetSpeed() * (1.0f - m_SlowPercent));
}

void TowerDefense::Enemy::Slow::OnRemove(Enemy& e)
{
	e.SetSpeed(e.GetSpeed() / (1.0f - m_SlowPercent));
}

void TowerDefense::Enemy::Slow::OnCombine(Enemy& e, std::shared_ptr<State> other)
{
	auto otherSlow = std::dynamic_pointer_cast<Slow>(other);
	if (otherSlow->m_SlowPercent > m_SlowPercent)
		m_SlowPercent = otherSlow->m_SlowPercent;
	if (otherSlow->m_TimeRemaining > m_TimeRemaining)
		m_TimeRemaining = otherSlow->m_TimeRemaining;
}

TowerDefense::Enemy::Stun::Stun(int time)
	:State(time, StateType::STUN)
{}

void TowerDefense::Enemy::Stun::OnApply(Enemy& e)
{
	m_TimeRemaining = (int)(m_TimeRemaining * (5.0f / (5.0f + e.GetStunResist())));
	e.SetStunned(true);
}

void TowerDefense::Enemy::Stun::OnRemove(Enemy& e)
{
	e.SetStunned(false);
}

void TowerDefense::Enemy::Stun::OnCombine(Enemy& e, std::shared_ptr<State> other)
{
	auto otherStun = std::dynamic_pointer_cast<Stun>(other);
	int otherTimeRemaining = (int)(otherStun->m_TimeRemaining * (5.0f / (5.0f + e.GetStunResist())));
	if (otherTimeRemaining > m_TimeRemaining)
	{
		m_TimeRemaining = otherStun->m_TimeRemaining;
		e.SetStunned(true);
	}
}

TowerDefense::Enemy::ArmorReduction::ArmorReduction(int time, float reductionPercent)
	:State(time, StateType::ARMORREDUCTION), m_ReductionPercent(reductionPercent)
{}

void TowerDefense::Enemy::ArmorReduction::OnApply(Enemy& e)
{
	e.SetArmor(e.GetArmor() * m_ReductionPercent);
}

void TowerDefense::Enemy::ArmorReduction::OnRemove(Enemy& e)
{
	e.SetArmor(e.GetArmor() / m_ReductionPercent);
}

void TowerDefense::Enemy::ArmorReduction::OnCombine(Enemy& e, std::shared_ptr<State> other)
{
	auto otherAR = std::dynamic_pointer_cast<ArmorReduction>(other);
	if (otherAR->m_ReductionPercent > m_ReductionPercent)
	{
		OnRemove(e);
		m_ReductionPercent = otherAR->m_ReductionPercent;
		OnApply(e);
	}
	if (otherAR->m_TimeRemaining > m_TimeRemaining)
		m_TimeRemaining = otherAR->m_TimeRemaining;
}

TowerDefense::Enemy::MagicResistReduction::MagicResistReduction(int time, float reductionPercent)
	:State(time, StateType::MAGICRESISTREDUCTION), m_ReductionPercent(reductionPercent)
{}

void TowerDefense::Enemy::MagicResistReduction::OnApply(Enemy& e)
{
	e.SetMagicResistance(e.GetMagicResistance() * m_ReductionPercent);
}

void TowerDefense::Enemy::MagicResistReduction::OnRemove(Enemy& e)
{
	e.SetMagicResistance(e.GetMagicResistance() / m_ReductionPercent);
}

void TowerDefense::Enemy::MagicResistReduction::OnCombine(Enemy& e, std::shared_ptr<State> other)
{
	auto otherMRR = std::dynamic_pointer_cast<MagicResistReduction>(other);
	if (otherMRR->m_ReductionPercent > m_ReductionPercent)
	{
		OnRemove(e);
		m_ReductionPercent = otherMRR->m_ReductionPercent;
		OnApply(e);
	}
	if (otherMRR->m_TimeRemaining > m_TimeRemaining)
		m_TimeRemaining = otherMRR->m_TimeRemaining;
}

TowerDefense::Enemy::Poison::Poison(int duration, float damage, unsigned int source, std::shared_ptr<Enemy> target)
	:State(duration, StateType::POISON), m_Damage(damage), m_PoisonTick(0), m_TickRate(30), m_Source(source), m_Target(target)
{}

void TowerDefense::Enemy::Poison::Update()
{
	State::Update();

	if (!Active())
		return;

	if (m_PoisonTick >= m_TickRate) {
		m_Target->TakeDamage(m_Damage, m_Source, Tower::DamageType::POISON);
		float totalPoisonDamage = m_Damage * (m_TimeRemaining / m_TickRate) * (100.0f / (100.0f + m_Target->GetMagicResistance()));
		m_Target->SetPoisonPercent(totalPoisonDamage / m_Target->GetHealth());
		m_PoisonTick = 0;
	}
	else
		m_PoisonTick += Combat::GetRoundSpeed();	
}

void TowerDefense::Enemy::Poison::OnApply(Enemy& e)
{
	float totalPoisonDamage = m_Damage * (m_TimeRemaining / m_TickRate) * (100.0f / (100.0f + e.GetMagicResistance()));
	e.SetPoisonPercent(totalPoisonDamage / e.GetHealth());
}

void TowerDefense::Enemy::Poison::OnRemove(Enemy& e)
{
	e.SetPoisonPercent(0.0f);
}

void TowerDefense::Enemy::Poison::OnCombine(Enemy& e, std::shared_ptr<State> other)
{
	auto otherPoison = std::dynamic_pointer_cast<Poison>(other);
	if (otherPoison->m_TimeRemaining > m_TimeRemaining)
		m_TimeRemaining = otherPoison->m_TimeRemaining;
	if (otherPoison->m_Damage > m_Damage)
	{
		m_Damage = otherPoison->m_Damage;
		m_Source = otherPoison->m_Source;
	}
}