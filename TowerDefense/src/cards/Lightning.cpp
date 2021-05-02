#include "pch.h"
#include "Lightning.h"
#include "scenes/Combat.h"
#include "core/Board.h"

TowerDefense::Lightning::Lightning()
	:Card("Lightning", CardType::SKILL, 20, "lightning", "lightningUpgraded"),
	m_LightningImage(std::make_unique<Image>("lightningImage", m_X, m_Y, 100, 100, 0.0f)),
	m_Damage(10.0f), m_Range(50.0f)
{

}

void TowerDefense::Lightning::Render()
{
	if (!m_OverBoard)
		Entity::Render();
	else
		m_LightningImage->Render();
}

void TowerDefense::Lightning::Update()
{
	if (Board::Get().Contains(m_X, m_Y))
	{
		m_OverBoard = true;
		m_LightningImage->SetPosition(m_X, m_Y, 0.0f);

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