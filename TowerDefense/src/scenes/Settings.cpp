#include "pch.h"
#include "Settings.h"
#include "TowerDefense.h"
#include "core/DropDown.h"

TowerDefense::Settings::Settings()
	:m_FocusedButton(-1)
{
	std::vector<std::string> fpsDropDownImages = std::vector<std::string>();
	fpsDropDownImages.push_back("30FPS");
	fpsDropDownImages.push_back("60FPS");
	fpsDropDownImages.push_back("uncappedFPS");

	m_Buttons =
	{
		std::make_unique<Button>(400.0f, 150.0f, 200, 50, "backButton"),
		std::make_unique<Button>(280.0f, 450.0f, 200, 50, "showFPS"),
		std::make_unique<DropDown>(520.0f, 450.0f, 200, 50, fpsDropDownImages)
	};
}

void TowerDefense::Settings::Render()
{
	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		if(i != m_FocusedButton)
			m_Buttons[i]->Render();

	if (m_FocusedButton != -1)
		m_Buttons[m_FocusedButton]->Render();
}

void TowerDefense::Settings::Update()
{
	//Check if a button requires focus
	m_FocusedButton = -1;
	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		if (m_Buttons[i]->RequiresFocus())
			m_FocusedButton = i;

	if (m_FocusedButton != -1)
		m_Buttons[m_FocusedButton]->Update();
	else
		for (unsigned int i = 0; i < m_Buttons.size(); i++)
			m_Buttons[i]->Update();

	//Return to MainMenu
	if (m_Buttons[0]->IsClicked())
	{
		SetScene(SceneType::MAINMENU);
	}
	//Show FPS Toggle
	else if (m_Buttons[1]->IsClicked())
	{
		bool showing = TowerDefense::FPSShowing();
		TowerDefense::ShowFPS(!showing);
		showing = !showing;
		if (showing)
			m_Buttons[1]->SetImages("hideFPS");
		else
			m_Buttons[1]->SetImages("showFPS");
	}
	else if (m_Buttons[2]->ValueChanged())
	{
		if (m_Buttons[2]->GetValue() == 0)
		{
			TowerDefense::SetFrameCap(60);
		}
		else if (m_Buttons[2]->GetValue() == 1)
		{
			TowerDefense::SetFrameCap(120);
		}
		else if (m_Buttons[2]->GetValue() == 2)
		{
			TowerDefense::SetFrameCap(0);
		}
	}
}

void TowerDefense::Settings::OnSwitch()
{
	bool showing = TowerDefense::FPSShowing();
	if (showing)
		m_Buttons[1]->SetImages("hideFPS");
	else
		m_Buttons[1]->SetImages("showFPS");

	int frameCap = TowerDefense::GetFrameCap();
	if(frameCap == 60)
		m_Buttons[2]->SetValue(0);
	else if(frameCap == 120)
		m_Buttons[2]->SetValue(1);
	else if(frameCap == 0)
		m_Buttons[2]->SetValue(2);
}