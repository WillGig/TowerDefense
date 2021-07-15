#include "pch.h"
#include "AnimalCompanion.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "core/Board.h"

TowerDefense::Tower::AnimalCompanion::AnimalCompanion(float damage, float attackSpeed, int range, float speed, const std::string& name, std::shared_ptr<Tower> master)
	:Tower(0.0f, 0.0f, 64, 64, attackSpeed, range, TowerType::DAMAGE, name),
	m_GoalX(0), m_GoalY(0), m_Speed(speed), m_Master(master), m_CurrentDirection(0.0f)
{
	m_PhysicalDamage = damage;

	SetX(m_Master->GetX());
	SetY(m_Master->GetY());
	FindGoal();
}

void TowerDefense::Tower::AnimalCompanion::Update()
{
	Tower::Update();
	if (m_Rotation != m_CurrentDirection)
		SetRotation(m_CurrentDirection);
	Move();
}

void TowerDefense::Tower::AnimalCompanion::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	float damage = m_PhysicalDamage;
	if (Random::GetFloat() < m_CritChance)
	{
		damage *= m_CritMultiplier;
		Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 32, 32, "critAnimation", 7, 30));
	}

	Combat::AddEntity(std::make_shared<TowerDefense::Feather>(m_X, m_Y, GetDirection(target), damage, GetID()));
}

void TowerDefense::Tower::AnimalCompanion::Move()
{
	if (Combat::Paused())
		return;

	for (int i = 0; i < Combat::GetRoundSpeed(); i++)
	{
		if (GetDistance(m_GoalX, m_GoalY) > 20.0f)
		{
			m_GoalDirection = atan2(m_GoalY - m_Y, m_GoalX - m_X) * 180 / PI - 90;
			
			while (m_Rotation > 180.0f)
				m_Rotation -= 360.0f;
			while (m_Rotation < -180.0f)
				m_Rotation += 360.0f;

			if (m_Rotation - m_GoalDirection > 4.0f)
			{
				if (m_Rotation - m_GoalDirection > 180.0f)
					SetRotation(m_Rotation + 4.0f);
				else
					SetRotation(m_Rotation - 4.0f);
			}
			else if (m_GoalDirection - m_Rotation > 4.0f)
			{
				if (m_GoalDirection - m_Rotation > 180.0f)
					SetRotation(m_Rotation - 4.0f);
				else
					SetRotation(m_Rotation + 4.0f);
			}

			if (abs(m_GoalDirection - m_Rotation) < 4.0f)
				m_Rotation = m_GoalDirection;

			SetX(m_X - m_Speed * sin(m_Rotation * PI / 180));
			SetY(m_Y + m_Speed * cos(m_Rotation * PI / 180));
			m_CurrentDirection = m_Rotation;
		}
		else
			FindGoal();
	}
}

//Find goal destination in master tower's range
void TowerDefense::Tower::AnimalCompanion::FindGoal()
{
	//Find a random point within the master tower's range on the board
	while (true)
	{
		float distance = Random::GetFloat() * (m_Master->GetRange()-25.0f) + 25.0f;
		float direction = Random::GetFloat() * 360;

		m_GoalX = m_Master->GetX() + distance * cos(m_GoalDirection * PI / 180.0f);
		m_GoalY = m_Master->GetY() + distance * sin(m_GoalDirection * PI / 180.0f);

		if(Board::Get().Contains(m_GoalX, m_GoalY))
			break;
	}
}

float TowerDefense::Tower::AnimalCompanion::GetDirection(std::shared_ptr<TowerDefense::Entity> e)
{
	return atan2(e->GetY() - m_Y, e->GetX() - m_X) * 180 / PI - 90;
}