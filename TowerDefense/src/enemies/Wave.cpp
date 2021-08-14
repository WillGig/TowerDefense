#include "pch.h"
#include "Wave.h"
#include "scenes/Combat.h"
#include "Enemies.h"

TowerDefense::Wave::Wave(const int enemies[], int size)
	:m_NextEnemy(0), m_Size(size/2), 
	m_Enemies(std::make_unique<std::vector<std::shared_ptr<Enemy::Enemy>>>()), 
	m_Delay(std::make_unique< std::vector<int>>())
{
	for (int i = 0; i + 1 < size; i += 2) {
		m_Delay->push_back(enemies[i + 1]);
		int type = enemies[i];
		switch (type) {
		case 0:
			m_Enemies->push_back(std::make_shared<Enemy::Rat>());
			break;
		case 1:
			m_Enemies->push_back(std::make_shared<Enemy::GiantRat>());
			break;
		case 2:
			m_Enemies->push_back(std::make_shared<Enemy::Goblin>());
			break;
		case 3:
			m_Enemies->push_back(std::make_shared<Enemy::Orc>());
			break;
		case 4:
			m_Enemies->push_back(std::make_shared<Enemy::BossRat>());
			break;
		case 5:
			m_Enemies->push_back(std::make_shared<Enemy::Beetle>());
			break;
		case 6:
			m_Enemies->push_back(std::make_shared<Enemy::Slime>());
			break;
		case 7:
			m_Enemies->push_back(std::make_shared<Enemy::Spider>());
			break;
		case 8:
			m_Enemies->push_back(std::make_shared<Enemy::ToughBeetle>());
			break;
		case 9:
			m_Enemies->push_back(std::make_shared<Enemy::Ooze>());
			break;
		case 10:
			m_Enemies->push_back(std::make_shared<Enemy::MegaOoze>());
			break;
		case 11:
			m_Enemies->push_back(std::make_shared<Enemy::DoubleOoze>());
			break;
		case 12:
			m_Enemies->push_back(std::make_shared<Enemy::JumpingOoze>());
			break;
		case 13:
			m_Enemies->push_back(std::make_shared<Enemy::Doubler>());
			break;
		case 14:
			m_Enemies->push_back(std::make_shared<Enemy::ShieldRat>());
			break;
		case 15:
			m_Enemies->push_back(std::make_shared<Enemy::ShamanRat>());
			break;
		case 16:
			m_Enemies->push_back(std::make_shared<Enemy::HealerRat>());
			break;
		case 17:
			m_Enemies->push_back(std::make_shared<Enemy::BlinkBug>());
			break;
		case 18:
			m_Enemies->push_back(std::make_shared<Enemy::RunnerBeetle>());
			break;
		case 19:
			m_Enemies->push_back(std::make_shared<Enemy::TankBeetle>());
			break;
		case 20:
			m_Enemies->push_back(std::make_shared<Enemy::PlagueRat>());
			break;
		case 21:
			m_Enemies->push_back(std::make_shared<Enemy::WitchRat>());
			break;
		case 22:
			m_Enemies->push_back(std::make_shared<Enemy::AssassinRat>());
			break;
		}
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