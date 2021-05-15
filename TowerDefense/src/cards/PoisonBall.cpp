#include "pch.h"
#include "SkillCards.h"
#include "core/Player.h"
#include "scenes/Combat.h"
#include "enemies/Enemy.h"
#include "core/Board.h"

TowerDefense::PoisonBall::PoisonBall()
	:Card("Poison Ball", CardType::SKILL, 20, "poisonBall", "poisonBallUpgraded"),
	m_PoisonAmount(1.0f), m_Radius(75.0f), m_PoisonTime(180),
	m_Circle(std::make_unique<Circle>(0.0f, 0.0f, m_Radius))
{
	m_Circle->SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	AddInfoCard(std::make_shared<InfoTile>("poisonInfo"));
}

void TowerDefense::PoisonBall::Render()
{
	if (m_OverBoard)
		m_Circle->Render();
	else
		Entity::Render();
}

void TowerDefense::PoisonBall::Update()
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

void TowerDefense::PoisonBall::Upgrade()
{
	Card::Upgrade();
	m_PoisonTime = 300;
}

bool TowerDefense::PoisonBall::CanPlay()
{
	return m_OverBoard;
}

void TowerDefense::PoisonBall::Play()
{
	m_OverBoard = false;

	//Slow all enemies in range
	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++) {
		std::shared_ptr<Entity> e = entities->at(i);
		if (e->GetEntityType() == Type::ENEMY)
		{
			if (e->GetDistance(m_X, m_Y) < m_Radius)
			{
				std::dynamic_pointer_cast<Enemy::Enemy>(e)->Poison(m_PoisonAmount, m_PoisonTime, GetID());
			}
		}
	}
	Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 100, 100, "acidExplosion", 7, 30));
}

std::shared_ptr<TowerDefense::Card> TowerDefense::PoisonBall::Clone()
{
	auto card = std::make_shared<PoisonBall>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}