#pragma once
#include "Enemy.h"

namespace TowerDefense
{
	class Wave
	{
	public:
		//Int array of enemies should alternate between a number representing the type of enemy followed by the delay between it and the previous enemy
		//Thus size should be double the length of the number of enemies in the wave
		//The size of enemies should NEVER be odd
		Wave(const int enemies[], int size);
		std::shared_ptr<Enemy::Enemy> GetNextEnemy();
		inline bool HasMoreEnemies() const { return m_NextEnemy < m_Size; }
		inline std::shared_ptr<Enemy::Enemy> Getenemy(int index) { return m_Enemies->at(index); }
		inline int NumberOfEnemies() { return m_Enemies->size(); }

	private:
		int m_NextEnemy, m_Size;
		std::unique_ptr<std::vector<std::shared_ptr<Enemy::Enemy>>> m_Enemies;
		//Delay before releasing the next enemy in updates (1 60th of a second)
		std::unique_ptr< std::vector<int>> m_Delay;
	};
}