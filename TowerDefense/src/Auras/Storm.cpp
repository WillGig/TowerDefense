#include "pch.h"
#include "Aura.h"
#include "scenes/combat.h"
#include "cards/LightningBolt.h"

TowerDefense::Aura::Storm::Storm(int damage)
	:Aura("Storm", "storm", "Playing cards strikes\nenemies with lightning\ndealing " + std::to_string(damage) + " damage"),
	m_Damage(damage)
{
}

void TowerDefense::Aura::Storm::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetID() == GetID())
		return;

	auto targets = GetTargets();

	if (targets.size() < 1)
		return;

	Vec2 prevTarget(targets[0]->GetX(), targets[0]->GetY());
	Vec2 currentTarget;

	targets[0]->TakeDamage((float)m_Damage, GetID(), Tower::DamageType::MAGIC);
	for (unsigned int i = 1; i < targets.size(); i++)
	{
		targets[i]->TakeDamage((float)m_Damage, GetID(), Tower::DamageType::MAGIC);
		currentTarget = Vec2(targets[i]->GetX(), targets[i]->GetY());
		//draw lightning connecting all targets
		Combat::AddEntity(std::make_shared<LightningBolt>(prevTarget, currentTarget));
		prevTarget = currentTarget;
	}
}

//Find all targets from lightning chaining between enemies in range of each other
std::vector<std::shared_ptr<TowerDefense::Enemy::Enemy>> TowerDefense::Aura::Storm::GetTargets()
{
	std::vector<std::shared_ptr<TowerDefense::Enemy::Enemy>> targets;

	std::shared_ptr<Enemy::Enemy> enemy;
	auto entities = Combat::GetEntities();
	int index = (int)(Random::GetFloat() * entities->size());
	
	for (unsigned int i = 0; i < entities->size(); i++)
	{
		auto e = entities->at(index);
		if (e->GetEntityType() == Type::ENEMY)
		{
			enemy = std::dynamic_pointer_cast<Enemy::Enemy>(e);
			break;
		}
		index++;
		if (index == entities->size())
			index = 0;
	}

	if (enemy)
		targets.push_back(enemy);
	else
		return targets;

	auto currentEnemy = enemy;
	while (auto enemy = GetEnemyInRange(currentEnemy, targets, 300.0f))
	{
		targets.push_back(enemy);
		currentEnemy = enemy;
	}

	return targets;
}

//Find the first enemy in range of the current target that is not already in the list
std::shared_ptr<TowerDefense::Enemy::Enemy> TowerDefense::Aura::Storm::GetEnemyInRange(std::shared_ptr<Enemy::Enemy> currentEnemy, std::vector<std::shared_ptr<Enemy::Enemy>> exclude, float range)
{
	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++) {
		std::shared_ptr<Entity> e = entities->at(i);
		if (e->GetEntityType() == Type::ENEMY && e->GetID() != currentEnemy->GetID() && !Contains(exclude, e->GetID()))
		{
			float distance = e->GetDistance(m_X, m_Y);
			if (distance < range)
				return std::dynamic_pointer_cast<Enemy::Enemy>(e);
		}
	}

	return nullptr;
}

bool TowerDefense::Aura::Storm::Contains(std::vector<std::shared_ptr<Enemy::Enemy>> list, unsigned int ID)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i]->GetID() == ID)
			return true;
	}
	return false;
}

void TowerDefense::Aura::Storm::Combine(std::shared_ptr<Aura> other)
{
	auto otherStorm = std::dynamic_pointer_cast<Storm>(other);
	if (otherStorm)
	{
		m_Damage += otherStorm->GetDamage();
		m_InfoText = std::make_unique<Text>("Playing cards strikes\nenemies with lightning\ndealing " + std::to_string(m_Damage) + " damage", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

const std::string TowerDefense::Aura::Storm::GetSaveData() const
{
	return "Storm\n" + std::to_string(m_Damage);
}