#include "pch.h"
#include "InGameSettings.h"
#include "TowerDefense.h"

TowerDefense::InGameSettings::InGameSettings()
	:m_Showing(false), m_Background(std::make_unique<Rectangle>(400.0f, 300.0f, 600.0f, 500.0f)),
	m_SettingsButton(std::make_unique<Button>(770.0f, 575.0f, 32, 32, "settingsIcon")),
	m_MainMenu(std::make_unique<Button>(400.0f, 100.0f, 180, 50, "backToMenuButton"))
{
	m_Background->SetColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void TowerDefense::InGameSettings::Render()
{
	RenderFade(0.9f);
	m_Background->Render();
	m_SettingsButton->Render();
	m_MainMenu->Render();
}

void TowerDefense::InGameSettings::Update()
{
	m_SettingsButton->Update();
	if (m_SettingsButton->IsClicked() || Input::GetKeyPressedAndSetFalse(GLFW_KEY_ESCAPE))
	{
		m_Showing = false;
		return;
	}

	m_MainMenu->Update();
	if (m_MainMenu->IsClicked())
	{
		TowerDefense::SetScene(SceneType::MAINMENU);
	}
}

void TowerDefense::InGameSettings::OnSwitch()
{

}

void TowerDefense::InGameSettings::UpdateButton()
{
	m_SettingsButton->Update();
	if (m_SettingsButton->IsClicked() || Input::GetKeyPressedAndSetFalse(GLFW_KEY_ESCAPE))
		Show(true);
}

TowerDefense::InGameSettings& TowerDefense::InGameSettings::Get()
{
	static InGameSettings instance;
	return instance;
}

void TowerDefense::InGameSettings::CleanUp()
{
	m_Background.reset();
	m_SettingsButton.reset();
	m_MainMenu.reset();
}