#include "pch.h"
#include "Projectile.h"
#include "TowerDefense.h"
#include "scenes/Combat.h"

TowerDefense::Projectile::Projectile(float x, float y, int width, int height, float speed, float rotation, float range, float damage, const std::string& image, unsigned int source)
	:Entity(x, y, width, height, rotation, image, Type::PROJECTILE), m_TurnSpeed(0.0f), m_Damage(damage), m_Speed(speed), m_Range(range),
	m_DistanceTraveled(0.0f), m_TowerSource(source)
{
	
}

void TowerDefense::Projectile::Update()
{
	if (Combat::Paused())
		return;

	UpdateDirection();
	
	Move();

	CheckCollisions();

	if (m_DistanceTraveled > m_Range)
		Destroy();

	if (OffScreen())
		Destroy();

}

void TowerDefense::Projectile::Destroy()
{
	Combat::RemoveEntity(m_ID);
}

//Updates direction for guided projectiles (turnspeed > 0)
void TowerDefense::Projectile::UpdateDirection()
{
	if (m_TurnSpeed == 0.0f)
		return;

	m_Target = FindTarget();
	if (m_Target)
	{
		float targetDirection = atan2(m_Target->GetY() - m_Y, m_Target->GetX() - m_X) * 180 / PI - 90;
		
		while (m_Rotation > 180.0f)
			m_Rotation -= 360.0f;
		while (m_Rotation < -180.0f)
			m_Rotation += 360.0f;

		for (int i = 0; i < Combat::GetRoundSpeed(); i++)
		{
			if (m_Rotation - targetDirection > m_TurnSpeed)
			{
				if (m_Rotation - targetDirection > 180.0f)
					SetRotation(m_Rotation + m_TurnSpeed);
				else
					SetRotation(m_Rotation - m_TurnSpeed);
			}
			else if (targetDirection - m_Rotation > m_TurnSpeed)
			{
				if (targetDirection - m_Rotation > 180.0f)
					SetRotation(m_Rotation - m_TurnSpeed);
				else
					SetRotation(m_Rotation + m_TurnSpeed);
			}
		}
	}
}

void TowerDefense::Projectile::Move()
{
	SetX(m_X - m_Speed * Combat::GetRoundSpeed() * sin(m_Rotation * PI / 180));
	SetY(m_Y + m_Speed * Combat::GetRoundSpeed() * cos(m_Rotation * PI / 180));
	m_DistanceTraveled += m_Speed * Combat::GetRoundSpeed();
}

void TowerDefense::Projectile::CheckCollisions()
{
	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++) {
		std::shared_ptr<TowerDefense::Entity> e = entities->at(i);
		if (e->GetEntityType() == Type::TOWER || e->GetEntityType() == Type::PROJECTILE || e->GetEntityType() == Type::ANIMATION)
			continue;

		float eX = e->GetX();
		float eY = e->GetY();
		int eW = e->GetWidth();
		int eH = e->GetHeight();

		if (!(m_X + m_Width/2 < eX - eW/2 || m_X - m_Width/2 > eX + eW/2 || m_Y + m_Height/2 < eY - eH/2 || m_Y - m_Height/2 > eY + eH/2)) {
			HitEntity(e);
			return;
		}
	}
}

bool TowerDefense::Projectile::OffScreen()
{
	return (m_X - m_Width / 2 < 0.0f || m_X + m_Width / 2 > 800.0f || m_Y - m_Height / 2 < 0.0f || m_Y + m_Height / 2 > 600.0f);
}

std::shared_ptr<TowerDefense::Enemy::Enemy> TowerDefense::Projectile::FindTarget()
{
	std::shared_ptr<TowerDefense::Enemy::Enemy> target;

	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++) {
		auto e = entities->at(i);

		if (e->GetEntityType() == Type::ENEMY)
		{
			auto enemy = std::dynamic_pointer_cast<TowerDefense::Enemy::Enemy>(e);

			if (!enemy->Visible())
				continue;

			//Prioritizes closest enemy
			if (!target || GetDistance(enemy->GetX(), enemy->GetY()) < GetDistance(target->GetX(), target->GetY()))
				target = enemy;
		}
	}

	return target;
}