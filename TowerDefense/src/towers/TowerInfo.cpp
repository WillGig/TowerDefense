#include "pch.h"
#include "TowerInfo.h"

TowerDefense::TowerInfo::TowerInfo(float x, float y)
	:Entity(200, 140, x, y, 0.0f, "TowerInfo", Type::STATICIMAGE), m_Dragging(false), 
	m_PreviousMouseX(0.0f), m_PreviousMouseY(0.0f)
{

}

void TowerDefense::TowerInfo::Update()
{
	if (!Input::GetLeftMouseClicked())
	{
		m_Dragging = false;
		return;
	}
		
	if (m_Dragging)
	{
		float currentMouseX = Input::GetMouseX();
		float currentMouseY = Input::GetMouseY();

		SetX(m_X + currentMouseX - m_PreviousMouseX);
		SetY(m_Y + currentMouseY - m_PreviousMouseY);

		m_PreviousMouseX = currentMouseX;
		m_PreviousMouseY = currentMouseY;
	}
	else if (Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetLeftMouseClicked())
	{
		m_Dragging = true;
		m_PreviousMouseX = Input::GetMouseX();
		m_PreviousMouseY = Input::GetMouseY();
	}
}