#pragma once
#include "Wave.h"

namespace TowerDefense
{
	class Fight
	{
	public:
		Fight(std::shared_ptr<std::vector<std::shared_ptr<Wave>>> waves);
		inline bool HasMoreWaves() const { return m_CurrentWave < (int)m_Waves->size() - 1; }
		inline std::shared_ptr<Wave> GetWave() const {return m_CurrentWave == -1 ? nullptr : m_Waves->at(m_CurrentWave); }
		inline void NextWave() { m_CurrentWave++; }

		std::unordered_map<std::string, int> m_DefeatedEnemies, m_EscapedEnemies;
		void AddDefeatedEnemy(const Enemy::Enemy& e);
		void AddEscapedEnemy(const Enemy::Enemy& e);
		void AddDamage(float amount, std::shared_ptr<Entity> source);
		inline int GetTowerDamage() const { return m_TowerDamage; };
		inline int GetSkillDamage() const { return m_SkillDamage; };
		inline int GetArtifactDamage() const { return m_ArtifactDamage; };

	private:
		int m_CurrentWave, m_TowerDamage, m_SkillDamage, m_ArtifactDamage;
		std::shared_ptr<std::vector<std::shared_ptr<Wave>>> m_Waves;
	};
}