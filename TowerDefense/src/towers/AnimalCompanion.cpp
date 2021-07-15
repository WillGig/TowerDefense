#include "pch.h"
#include "AnimalCompanion.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "core/Board.h"

TowerDefense::Tower::AnimalCompanion::AnimalCompanion(float damage, float attackSpeed, int range, float speed, const std::string& name, std::shared_ptr<Tower> master)
	:Tower(0.0f, 0.0f, 64, 64, attackSpeed, range, TowerType::DAMAGE, name),
	m_GoalX(0), m_GoalY(0), m_Speed(speed), m_Master(master)
{
	m_PhysicalDamage = damage;

	SetX(m_Master->GetX());
	SetY(m_Master->GetY());

	FindGoal();
}

void TowerDefense::Tower::AnimalCompanion::Update()
{
	Tower::Update();
	Move();
	if (m_Rotation != m_GoalDirection)
		SetRotation(m_GoalDirection);
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
		if (GetDistance(m_GoalX, m_GoalY) > m_Speed)
		{
			SetX(m_X + m_SpeedX);
			SetY(m_Y + m_SpeedY);
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
		float distance = Random::GetFloat() * m_Master->GetRange();
		float direction = Random::GetFloat() * 360;

		m_GoalX = m_Master->GetX() + distance * cos(m_GoalDirection * PI / 180.0f);
		m_GoalY = m_Master->GetY() + distance * sin(m_GoalDirection * PI / 180.0f);

		if(Board::Get().Contains(m_GoalX, m_GoalY))
			break;
	}

	//calculate the speed to get to that point and the direction to face
	float distanceFromLocation = GetDistance(m_GoalX, m_GoalY);

	m_SpeedX = m_Speed * (m_GoalX - m_X) / distanceFromLocation;
	m_SpeedY = m_Speed * (m_GoalY - m_Y) / distanceFromLocation;

	m_GoalDirection = atan2(m_GoalY - m_Y, m_GoalX - m_X) * 180 / PI - 90;
	SetRotation(m_GoalDirection);
}

float TowerDefense::Tower::AnimalCompanion::GetDirection(std::shared_ptr<TowerDefense::Entity> e)
{
	return atan2(e->GetY() - m_Y, e->GetX() - m_X) * 180 / PI - 90;
}