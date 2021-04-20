#include "pch.h"
#include "FireBall.h"
#include "core/Player.h"
#include "scenes/Combat.h"
#include "enemies/Enemy.h"
#include "core/Board.h"

TowerDefense::FireBall::FireBall()
	:Card("Fire Ball", 20, "fireBall", "fireBallUpgraded"), 
	m_Damage(10.0f), m_Radius(50.0f), m_Circle(std::make_unique<Circle>(0.0f, 0.0f, m_Radius))
{
	m_Circle->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void TowerDefense::FireBall::Render()
{
	if (m_OverBoard)
		m_Circle->Render();
	else
		Entity::Render();
}

void TowerDefense::FireBall::Update()
{
	if (TowerDefense::Board::Get().Contains(m_X, m_Y))
	{
		m_OverBoard = true;

		m_Circle->SetPosition(m_X, m_Y, 0.0f);

		//Highlight all enemies in range
		auto entities = Combat::GetEntities();
		for (unsigned int i = 0; i < entities->size(); i++) {
			std::shared_ptr<Entity> e = entities->at(i);
			if (e->GetEntityType() == Type::ENEMY)
			{
				if (e->GetDistance(m_X, m_Y) < m_Radius)
				{
					std::dynamic_pointer_cast<Enemy::Enemy>(e)->SetSelected(true);
				}
			}
		}
	}
	else
	{
		m_OverBoard = false;
	}
}

void TowerDefense::FireBall::Upgrade()
{
	Card::Upgrade();
	m_Damage = 15.0f;
}

bool TowerDefense::FireBall::Play()
{
	if (m_OverBoard) {
		m_OverBoard = false;

		//Damage all enemies in range
		auto entities = Combat::GetEntities();
		for (unsigned int i = 0; i < entities->size(); i++) {
			std::shared_ptr<Entity> e = entities->at(i);
			if (e->GetEntityType() == Type::ENEMY)
			{
				if (e->GetDistance(m_X, m_Y) < m_Radius)
				{
					std::dynamic_pointer_cast<Enemy::Enemy>(e)->TakeDamage(m_Damage);
				}
			}
		}
		Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 100, 100, "explosion", 7, 30));
		return true;
	}
	return false;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::FireBall::Clone()
{
	auto card = std::make_shared<FireBall>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}