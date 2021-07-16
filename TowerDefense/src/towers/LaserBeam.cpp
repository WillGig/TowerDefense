#include "pch.h"
#include "LaserBeam.h"
#include "scenes/Combat.h"

TowerDefense::LaserBeam::LaserBeam(std::shared_ptr<Entity> source, std::shared_ptr<Enemy::Enemy> target)
	:Entity((source->GetX() + target->GetX())/2.0f, (source->GetY() + target->GetY()) / 2.0f,
		(int)abs(source->GetX() - target->GetX()), (int)abs(source->GetY() - target->GetY()), 0.0f, "", Type::ANIMATION),
	m_Line(Vec2(source->GetX(), source->GetY()), Vec2(target->GetX(), target->GetY())), 
	m_Circle(target->GetX(), target->GetY(), 10.0f), m_Source(source), 
	m_Target(target), m_CircleRadius(10.0f), m_CircleChange(1.0f)
{
	m_Line.SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_Line.SetThickness(6.0f);
	m_Circle.SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_Circle.SetThickness(10.0f);
}

void TowerDefense::LaserBeam::Update()
{
	m_Line = Line(Vec2(m_Source->GetX(), m_Source->GetY()), Vec2(m_Target->GetX(), m_Target->GetY()));
	m_Line.SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_Line.SetThickness(6.0f);

	m_CircleRadius += Combat::GetRoundSpeed();
	m_Circle = Circle(m_Target->GetX(), m_Target->GetY(), m_CircleRadius);
	m_Circle.SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_Circle.SetThickness(m_CircleRadius);
}

void TowerDefense::LaserBeam::Render()
{
	if (m_Target->GetHealth() > 0)
	{
		m_Line.Render();
		m_Circle.Render();
	}
}