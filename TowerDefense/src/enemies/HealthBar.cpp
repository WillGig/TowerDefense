#include "pch.h"
#include "HealthBar.h"

TowerDefense::HealthBar::HealthBar(float x, float y, float width, float height)
	:m_X(x), m_Y(y), m_Width(width), m_Height(height), m_Color(1.0f, 0.0f, 0.0f, 1.0f),
	m_Image(std::make_unique<Rectangle>(x, y, width, height))
{
	m_Image->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void TowerDefense::HealthBar::Render()
{
	m_Image->Render();
}

void TowerDefense::HealthBar::SetFill(float percent)
{
	m_Image = std::make_unique<Rectangle>(m_X, m_Y, m_Width * percent, m_Height);
	m_Image->SetColor(m_Color.w, m_Color.x, m_Color.y, m_Color.z);
}

void TowerDefense::HealthBar::SetColor(float r, float g, float b, float a)
{
	m_Color = Vec4(r, g, b, a);
	m_Image->SetColor(r, g, b, a);
}

void TowerDefense::HealthBar::SetPosition(float x, float y)
{
	m_X = x;
	m_Y = y;
	m_Image->SetPosition(m_X, m_Y, 1.0f);
}