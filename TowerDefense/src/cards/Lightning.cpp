#include "pch.h"
#include "Lightning.h"
#include "scenes/Combat.h"
#include "core/Board.h"
#include "LightningBolt.h"

TowerDefense::Lightning::Lightning()
	:Card("Lightning", CardType::SKILL, 20, "lightning", "lightningUpgraded"),
	m_Damage(5.0f), m_Range(50.0f)
{
	m_Exhausts = true;
	AddInfoCard(std::make_shared<InfoTile>("exhaustInfo"));
}

void TowerDefense::Lightning::Render()
{
	if (!m_OverBoard)
		Entity::Render();
	else
	{
		//render ball of lightning
		if ((Time::Get().GetTime()) % 4 == 0)
		{
			float rot = Random::GetFloat() * PI;
			float rad = Random::GetFloat() * 20.0f + 20.0f;
			float x = rad * cos(rot);
			float y = rad * sin(rot);
			Combat::AddEntity(std::make_shared<LightningBolt>(Vec2(m_X - x, m_Y - y), Vec2(m_X + x, m_Y + y)));
		}
	}
}

void TowerDefense::Lightning::Update()
{
	if (Board::Get().Contains(m_X, m_Y))
	{
		m_OverBoard = true;

		//Highlight all enemies in range
		std::shared_ptr<Enemy::Enemy> e = GetClosestEnemy();
		if (e && e->GetDistance(m_X, m_Y) < m_Range)
			e->SetSelected(true);
	}
	else
	{
		m_OverBoard = false;
	}
}

void TowerDefense::Lightning::Upgrade()
{
	Card::Upgrade();
	m_Damage = 10.0f;
}

bool TowerDefense::Lightning::Play()
{
	if (m_OverBoard) {
		m_OverBoard = false;

		std::shared_ptr<Enemy::Enemy> e = GetClosestEnemy();

		if (e && e->GetDistance(m_X, m_Y) < m_Range)
		{
			auto targets = GetTargets(e);

			Vec2 prevTarget(e->GetX(), e->GetY());
			Vec2 currentTarget;

			e->TakeDamage(m_Damage, GetID());
			for (unsigned int i = 1; i < targets.size(); i++)
			{
				targets[i]->TakeDamage(m_Damage, GetID());
				currentTarget = Vec2(targets[i]->GetX(), targets[i]->GetY());
				//draw lightning connecting all targets
				Combat::AddEntity(std::make_shared<LightningBolt>(prevTarget, currentTarget));
				prevTarget = currentTarget;
			}
			return true;
		}
	}
	return false;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Lightning::Clone()
{
	auto card = std::make_shared<Lightning>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}

std::shared_ptr<TowerDefense::Enemy::Enemy> TowerDefense::Lightning::GetClosestEnemy()
{
	float closestDistance = 0;
	std::shared_ptr<Enemy::Enemy> closestEnemy;

	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++) {
		std::shared_ptr<Entity> e = entities->at(i);
		if (e->GetEntityType() == Type::ENEMY)
		{
			float distance = e->GetDistance(m_X, m_Y);
			if (distance < closestDistance || closestDistance == 0)
			{
				closestEnemy = std::dynamic_pointer_cast<Enemy::Enemy>(e);
				closestDistance = distance;
			}
		}
	}

	return closestEnemy;
}

//Find all targets from lightning chaining between enemies in range of each other
std::vector<std::shared_ptr<TowerDefense::Enemy::Enemy>> TowerDefense::Lightning::GetTargets(std::shared_ptr<Enemy::Enemy> e)
{
	std::vector<std::shared_ptr<TowerDefense::Enemy::Enemy>> targets;

	targets.push_back(e);
	
	auto currentEnemy = e;
	while (auto enemy = GetEnemyInRange(currentEnemy, targets, 300.0f))
	{
		targets.push_back(enemy);
		currentEnemy = enemy;
	}

	return targets;
}

//Find the first enemy in range of the current target that is not already in the list
std::shared_ptr<TowerDefense::Enemy::Enemy> TowerDefense::Lightning::GetEnemyInRange(std::shared_ptr<Enemy::Enemy> currentEnemy, std::vector<std::shared_ptr<Enemy::Enemy>> exclude, float range)
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

bool TowerDefense::Lightning::Contains(std::vector<std::shared_ptr<Enemy::Enemy>> list, unsigned int ID)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i]->GetID() == ID)
			return true;
	}
	return false;
}