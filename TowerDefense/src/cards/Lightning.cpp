#include "pch.h"
#include "Lightning.h"
#include "scenes/Combat.h"
#include "core/Board.h"
#include "LightningBolt.h"

TowerDefense::Lightning::Lightning()
	:Card("Lightning", CardType::SKILL, 20, "lightning", "lightningUpgraded"),
	m_Damage(10.0f), m_Range(50.0f)
{

}

void TowerDefense::Lightning::Render()
{
	if (!m_OverBoard)
		Entity::Render();
	else
	{
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
	m_Damage = 15.0f;
}

bool TowerDefense::Lightning::Play()
{
	if (m_OverBoard) {
		m_OverBoard = false;

		std::shared_ptr<Enemy::Enemy> e = GetClosestEnemy();

		if (e && e->GetDistance(m_X, m_Y) < m_Range)
		{
			//TODO: Lightning stuff
			Combat::AddEntity(std::make_shared<LightningBolt>(Vec2(200.0f, 300.0f), Vec2(600.0f, 300.0f)));
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