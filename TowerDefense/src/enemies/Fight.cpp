#include "pch.h"
#include "Fight.h"
#include "scenes/Combat.h"

TowerDefense::Fight::Fight(std::shared_ptr<std::vector<std::shared_ptr<Wave>>> waves)
	:m_CurrentWave(-1), m_Waves(waves), m_TowerDamage(0), m_SkillDamage(0), m_AuraDamage(0), m_ArtifactDamage(0),
	m_DefeatedEnemies(std::unordered_map<std::string, int>()), 
	m_EscapedEnemies(std::unordered_map<std::string, int>())
{

}

void TowerDefense::Fight::AddDefeatedEnemy(const Enemy::Enemy& e)
{
	std::string name = e.GetName();
	if (m_DefeatedEnemies.find(name) != m_DefeatedEnemies.end())
	{
		m_DefeatedEnemies.at(name)++;
		return;
	}
	m_DefeatedEnemies.insert({ name, 1 });
}

void TowerDefense::Fight::AddEscapedEnemy(const Enemy::Enemy& e)
{
	std::string name = e.GetName();
	if (m_EscapedEnemies.find(name) != m_EscapedEnemies.end())
	{
		m_EscapedEnemies.at(name)++;
		return;
	}
	m_EscapedEnemies.insert({ name, 1 });
}

void TowerDefense::Fight::AddDamage(float amount, std::shared_ptr<Entity> source)
{

	Type s = source->GetEntityType();
	
	if (s == Type::TOWER)
		m_TowerDamage += amount;
	else if (s == Type::CARD)
		m_SkillDamage += amount;
	else if (s == Type::AURA)
		m_AuraDamage += amount;
	else if (s == Type::ARTIFACT)
		m_ArtifactDamage += amount;
}