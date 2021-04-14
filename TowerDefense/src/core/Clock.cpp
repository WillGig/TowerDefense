#include "pch.h"
#include "Clock.h"

TowerDefense::Time::Time()
	:m_Time(0)
{
}

TowerDefense::Time& TowerDefense::Time::Get()
{
	static TowerDefense::Time instance;
	return instance;
}

void TowerDefense::Time::Update()
{
	m_Time++;
}

int TowerDefense::Time::GetTime()
{
	return m_Time;
}