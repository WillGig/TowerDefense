#include "pch.h"
#include "Settings.h"
#include "TowerDefense.h"

TowerDefense::Settings::Settings()
{
	m_Buttons =
	{
		std::make_unique<Button>(400.0f, 150.0f, 200, 50, "backButton"),
		std::make_unique<Button>(400.0f, 450.0f, 200, 50, "showFPS")
	};
}

void TowerDefense::Settings::Render()
{
	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->Render();
}

void TowerDefense::Settings::Update()
{
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
}

void TowerDefense::Settings::OnSwitch()
{

}