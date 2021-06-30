#include "pch.h"
#include "Aura.h"

TowerDefense::Aura::Aura(const std::string name, const std::string info)
	:Entity(0.0f, 0.0f, 32, 32, 0.0f, name, Type::AURA), m_Name(name), m_Selected(false),
	m_InfoImage(std::make_unique<Image>("InfoImage", 0.0f, 0.0f, 220, 100, 0.0f)),
	m_InfoText(std::make_unique<Text>(info, 0.0f, 0.0f, 10.0f, 0.0f))
{
	m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::Aura::Render()
{
	Entity::Render();
	if (m_Selected)
	{
		m_InfoImage->Render();
		m_InfoText->Render();
	}
}

void TowerDefense::Aura::Update()
{
	if (Contains(Input::GetMouseX(), Input::GetMouseY()))
		m_Selected = true;
	else
		m_Selected = false;
}

void TowerDefense::Aura::SetX(float x)
{
	Entity::SetX(x);
	m_InfoImage->SetPosition(m_X, m_Y + 70, 0.0f);
	m_InfoText->SetPosition(m_X, m_Y + 80, 0.0f);
}

void TowerDefense::Aura::SetY(float y)
{
	Entity::SetY(y);
	m_InfoImage->SetPosition(m_X, m_Y + 70, 0.0f);
	m_InfoText->SetPosition(m_X, m_Y + 80, 0.0f);
}