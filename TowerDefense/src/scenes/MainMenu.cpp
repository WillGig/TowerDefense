#include "pch.h"
#include "MainMenu.h"
#include "TowerDefense.h"

TowerDefense::MainMenu::MainMenu()
{
	m_Buttons =
	{
		std::make_unique<Button>(200, 50, 400.0f, 350.0f, "res/textures/newGameButton.png", "res/textures/newGameButtonSelected.png"),
		std::make_unique<Button>(200, 50, 400.0f, 300.0f, "res/textures/loadGameButton.png", "res/textures/loadGameButtonSelected.png"),
		std::make_unique<Button>(200, 50, 400.0f, 250.0f, "res/textures/settingsButton.png", "res/textures/settingsButtonSelected.png"),
		std::make_unique<Button>(200, 50, 400.0f, 200.0f, "res/textures/exitButton.png", "res/textures/exitButtonSelected.png"),
	};
}

void TowerDefense::MainMenu::Render()
{
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
		SetScene(SceneType::BASE);
	}
	//Saving and Loading
	else if (m_Buttons[1]->IsClicked())
	{

	}
	//Settings Menu
	else if (m_Buttons[2]->IsClicked())
	{

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