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