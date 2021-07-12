#include "pch.h"
#include "ClickCircle.h"

TowerDefense::ClickCircle::ClickCircle(float x, float y, float radius, float changeSpeed)
	:Entity(x, y, (int)(radius * 2), (int)(radius * 2), 0.0f, "", Type::ANIMATION), 
	m_Radius(radius), m_ChangeSpeed(changeSpeed), m_Remove(false), m_Clicked(false), m_CircleImage(x, y, radius)
{}

void TowerDefense::ClickCircle::Update()
{
	if (Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetLeftMouseClickedAndSetFalse())
	{
		m_Remove = true;
		m_Clicked = true;
		return;
	}

	m_Radius -= m_ChangeSpeed;
	if (m_Radius > 0)
		m_CircleImage = Circle(m_X, m_Y, m_Radius);
	else
		m_Remove = true;
}

void TowerDefense::ClickCircle::Render()
{
	m_CircleImage.Render();
}

bool TowerDefense::ClickCircle::Contains(float x, float y) const
{
	return GetDistance(x, y) < m_Radius;
}