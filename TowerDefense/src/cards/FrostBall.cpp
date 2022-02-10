#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"
#include "scenes/Combat.h"
#include "enemies/Enemy.h"
#include "core/Board.h"
#include "enemies/States/State.h"

TowerDefense::FrostBall::FrostBall()
	:Card("Frost Ball", CardType::SKILL, 0, "frostBall", "frostBallUpgraded"),
	m_SlowPercent(0.8f), m_Radius(75.0f), m_SlowTime(180), 
	m_Circle(std::make_unique<Circle>(0.0f, 0.0f, m_Radius))
{
	m_Circle->SetColor(0.0f, 0.0f, 1.0f, 1.0f);
	AddInfoCard(std::make_shared<InfoTile>("slowInfo"));
}

void TowerDefense::FrostBall::Render()
{
	if (m_OverBoard)
		m_Circle->Render();
	else
		Entity::Render();
}

void TowerDefense::FrostBall::Update()
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

void TowerDefense::FrostBall::Upgrade()
{
	Card::Upgrade();
	m_SlowTime = 300;
}

bool TowerDefense::FrostBall::CanPlay()
{
	return m_OverBoard;
}

void TowerDefense::FrostBall::Play()
{
	m_OverBoard = false;

	//Slow all enemies in range
	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++) {
		std::shared_ptr<Entity> e = entities->at(i);
		if (e->GetEntityType() == Type::ENEMY)
		{
			if (e->GetDistance(m_X, m_Y) < m_Radius)
				std::dynamic_pointer_cast<Enemy::Enemy>(e)->ApplyState(std::make_shared < Enemy::Slow>(m_SlowTime, m_SlowPercent));
		}
	}
	Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 100, 100, "frostExplosion", 7, 30));
}

std::shared_ptr<TowerDefense::Card> TowerDefense::FrostBall::Clone()
{
	auto card = std::make_shared<FrostBall>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}