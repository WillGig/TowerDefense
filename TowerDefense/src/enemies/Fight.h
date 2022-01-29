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
		inline std::shared_ptr<Wave> GetWave(int index) const { return m_Waves->at(index); }
		inline void NextWave() { m_CurrentWave++; }
		inline int GetCurrentWave() const { return m_CurrentWave; }
		inline int GetNumberOfWaves() const { return (int)m_Waves->size(); }

		std::unordered_map<std::string, std::pair<int, int>> m_DefeatedEnemies, m_EscapedEnemies;
		void AddDefeatedEnemy(const Enemy::Enemy& e);
		void AddEscapedEnemy(const Enemy::Enemy& e);
		void AddDamage(float amount, std::shared_ptr<Entity> source);
		inline int GetTowerDamage() const { return (int)m_TowerDamage; }
		inline int GetSkillDamage() const { return (int)m_SkillDamage; }
		inline int GetAuraDamage() const { return (int)m_AuraDamage; }
		inline int GetArtifactDamage() const { return (int)m_ArtifactDamage; }

	private:
		int m_CurrentWave;
		float m_TowerDamage, m_SkillDamage, m_AuraDamage, m_ArtifactDamage;
		std::shared_ptr<std::vector<std::shared_ptr<Wave>>> m_Waves;
	};
}