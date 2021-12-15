#include "pch.h"
#include "DropDown.h"

TowerDefense::DropDown::DropDown(float x, float y, int width, int height, std::vector<std::string> images)
	:Button(x, y, width, height, images[0]), m_ValueChanged(false),
	m_Buttons(std::make_unique<std::vector<std::unique_ptr<Button>>>())
{
	for (unsigned int i = 0; i < images.size(); i++)
		m_Buttons->push_back(std::make_unique<Button>(x, y - height * i, width, height, images[i]));
}

void TowerDefense::DropDown::Render()
{
	Button::Render();
	if (m_RequiresFocus)
	{
		for (unsigned int i = 0; i < m_Buttons->size(); i++)
			m_Buttons->at(i)->Render();
	}
}

void TowerDefense::DropDown::Update()
{
	if (m_RequiresFocus)
	{
		for (unsigned int i = 0; i < m_Buttons->size(); i++)
		{
			m_Buttons->at(i)->Update();
			if (m_Buttons->at(i)->IsClicked())
			{
				if (m_Value != i)
				{
					m_Value = i;
					SetImages(m_Buttons->at(i)->GetImageName());
					m_ValueChanged = true;
				}
				m_RequiresFocus = false;
				if (i != 0)
					SetSelected(false);
			}
		}

		if (Input::GetLeftMouseClickedAndSetFalse())
		{
			m_RequiresFocus = false;
			SetSelected(false);
		}
			
	}
	else
	{
		Button::Update();
		if (IsClicked())
			m_RequiresFocus = true;
	}
}

void TowerDefense::DropDown::SetValue(int value)
{
	if (value > (int)m_Buttons->size() - 1)
		return;

	m_Value = value;
	SetImages(m_Buttons->at(value)->GetImageName());
}