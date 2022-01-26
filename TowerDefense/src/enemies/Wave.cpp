#include "pch.h"
#include "Wave.h"
#include "scenes/Combat.h"
#include "Enemies.h"

TowerDefense::Wave::Wave(const int enemies[], int size)
	:m_NextEnemy(0), m_Size(size/2), 
	m_Enemies(std::make_unique<std::vector<std::shared_ptr<Enemy::Enemy>>>()), 
	m_Delay(std::make_unique< std::vector<int>>())
{
	using namespace Enemy;

	for (int i = 0; i + 1 < size; i += 2) {
		m_Delay->push_back(enemies[i + 1]);
		int type = enemies[i];
		m_Enemies->push_back(GetEnemy(type));
	}
}

//If the next enemy is ready to be spawned, returns the enemy
//Otherwise returns nullptr and decrements the time for the next enemy
//called every update during combat
std::shared_ptr<TowerDefense::Enemy::Enemy> TowerDefense::Wave::GetNextEnemy()
{
	if (m_Delay->at(m_NextEnemy) <= 0) {
		m_NextEnemy++;
		return m_Enemies->at(m_NextEnemy - 1);
	}
	
	m_Delay->at(m_NextEnemy) -= Combat::GetRoundSpeed();
	return nullptr;
}