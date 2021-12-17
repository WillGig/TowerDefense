#include "pch.h"
#include "MainMenu.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "Combat.h"
#include "Base.h"

TowerDefense::MainMenu::MainMenu()
	:m_Title(std::make_unique<Text>("Tower Defense", 400.0f, 450.0f, 40.0f, 0.0f))
{
	m_Title->SetColor(0.7f, 0.7f, 0.7f, 1.0f);

	m_Buttons =
	{
		std::make_unique<Button>(400.0f, 350.0f, 200, 50, "newGameButton"),
		std::make_unique<Button>(400.0f, 300.0f, 200, 50, "loadGameButton"),
		std::make_unique<Button>(400.0f, 250.0f, 200, 50, "settingsButton"),
		std::make_unique<Button>(400.0f, 200.0f, 200, 50, "exitButton"),
	};
}

void TowerDefense::MainMenu::Render()
{
	m_Title->Render();

	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->Render();
}

void TowerDefense::MainMenu::Update()
{
	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->Update();

	//Start New Game
	if (m_Buttons[0]->IsClicked())
	{
		SetScene(SceneType::NEWGAMEMENU);
	}
	//Load Game
	else if (m_Buttons[1]->IsClicked())
	{
		SetScene(SceneType::LOADMENU);
	}
	//Settings Menu
	else if (m_Buttons[2]->IsClicked())
	{
		SetScene(SceneType::SETTINGS);
	}
	//Exit
	else if (m_Buttons[3]->IsClicked())
	{
		Stop();
	}
}

void TowerDefense::MainMenu::OnSwitch()
{

}