#include "pch.h"
#include "HealthBar.h"

TowerDefense::HealthBar::HealthBar(float x, float y, float width, float height)
	:m_X(x), m_Y(y), m_Width(width), m_Height(height),
	m_Image(std::make_unique<Rectangle>(x, y, width, height)),
	m_PoisonBar(std::make_unique<Rectangle>(x, y, 0.0f, height))
{
	m_Image->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void TowerDefense::HealthBar::Render()
{
	m_Image->Render();
	m_PoisonBar->Render();
}

void TowerDefense::HealthBar::SetFill(float percent, float poisonPercent)
{
	if (poisonPercent > 1.0f)
		poisonPercent = 1.0f;
	float poisonSize = m_Width * percent * poisonPercent;
	float healthSize = m_Width * percent - poisonSize;
	m_Image = std::make_unique<Rectangle>(m_X - poisonSize/2, m_Y, healthSize, m_Height);
	m_Image->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_PoisonBar = std::make_unique<Rectangle>(m_X + healthSize /2, m_Y, poisonSize, m_Height);
	m_PoisonBar->SetColor(0.0f, 1.0f, 0.0f, 1.0f);
}

void TowerDefense::HealthBar::SetPosition(float x, float y)
{
	m_X = x;
	m_Y = y;

	float poisonSize = m_PoisonBar->GetWidth();
	float healthSize = m_Image->GetWidth();

	m_Image->SetPosition(m_X - poisonSize / 2, m_Y, 1.0f);
	m_PoisonBar->SetPosition(m_X + healthSize / 2, m_Y, 1.0f);
}