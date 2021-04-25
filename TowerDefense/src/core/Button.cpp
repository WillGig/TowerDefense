#include "pch.h"
#include "Button.h"
#include "TowerDefense.h"

TowerDefense::Button::Button(float x, float y, int width, int height, const std::string& image)
	:Entity(x, y, width, height, 0.0f, image, Type::BUTTON), m_Selected(false), m_Clicked(false),
	m_RegularImage(std::make_shared<Image>(image, x, y, width, height, 0.0f)), 
	m_SelectedImage(std::make_shared<Image>(image + "Selected", x, y, width, height, 0.0f))
{
}

void TowerDefense::Button::Update()
{
	m_Clicked = false;
	if (Contains(Input::GetMouseX(), Input::GetMouseY()))
	{
		m_Selected = true;
		SetImage(m_SelectedImage);
		if (Input::GetLeftMouseClickedAndSetFalse())
		{
			m_Clicked = true;
		}
	}
	else
	{
		m_Selected = false;
		SetImage(m_RegularImage);
	}
}

void TowerDefense::Button::SetSelected(bool selected)
{
	m_Selected = selected;
	if (m_Selected)
		SetImage(m_SelectedImage);
	else
		SetImage(m_RegularImage);
}

void TowerDefense::Button::SetImages(const std::string& image)
{
	m_RegularImage = std::make_shared<Image>(image, m_X, m_Y, m_Width, m_Height, 0.0f);
	m_SelectedImage = std::make_shared<Image>(image + "Selected", m_X, m_Y, m_Width, m_Height, 0.0f);
}