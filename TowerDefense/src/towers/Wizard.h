#pragma once
#include "Tower.h"
#include "enemies/Enemy.h"
#include "core/Tile.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Wizard : public Tower
		{
		public:
			Wizard();
			Wizard(float fireTime, int range, float damage, int numberOfMissiles);
			std::shared_ptr<Tower> Clone();

			bool CanUpgrade() override;

			inline int GetNumberOfMissiles() const { return m_NumberOfMissiles; }
			inline void SetNumberOfMissiles(int num) { m_NumberOfMissiles = num; }

			inline int GetGraveMissileFrequency() const { return m_GraveMissileFrequency; }
			inline void SetGraveMissileFrequency(int num) { m_GraveMissileFrequency = num; }

			inline bool GetSummonner() const { return m_Summoner; }
			inline void SetSummonner(bool sum) { m_Summoner = sum; }

			inline void SetLightning(bool l) { m_Lightning = l; }

		private:
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> GetPossibleUpgrades() override;
			
			std::vector<std::shared_ptr<TowerDefense::Enemy::Enemy>> GetTargets(std::shared_ptr<Enemy::Enemy> e);
			std::shared_ptr<TowerDefense::Enemy::Enemy> GetEnemyInRange(std::shared_ptr<Enemy::Enemy> currentEnemy, std::vector<std::shared_ptr<Enemy::Enemy>> exclude, float range);
			bool Contains(std::vector<std::shared_ptr<Enemy::Enemy>> list, unsigned int ID);

			void Summon();
			std::shared_ptr<TowerDefense::Tile> GetRandomTile();
			std::shared_ptr<Tower> GetRandomSummon();

			int m_NumberOfMissiles, m_GraveMissileFrequency, m_GraveMissileTimer;
			bool m_Lightning, m_Summoner;
		};
	}
	
}