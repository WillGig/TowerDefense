#include "pch.h"
#include "LoadMenu.h"
#include "TowerDefense.h"
#include "core/SaveLoad.h"

TowerDefense::LoadMenu::LoadMenu()
	:m_Title(std::make_unique<Text>("Tower Defense", 400.0f, 450.0f, 40.0f, 0.0f))
{
	m_Title->SetColor(0.7f, 0.7f, 0.7f, 1.0f);
	m_Buttons =
	{
		std::make_unique<Button>(400.0f, 350.0f, 200, 50, "slot1"),
		std::make_unique<Button>(400.0f, 300.0f, 200, 50, "slot2"),
		std::make_unique<Button>(400.0f, 250.0f, 200, 50, "slot3"),
		std::make_unique<Button>(400.0f, 150.0f, 200, 50, "backButton")
	};
}

void TowerDefense::LoadMenu::Render()
{
	m_Title->Render();
	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->Render();
}

void TowerDefense::LoadMenu::Update()
{
	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->Update();

	//Save Slots
	for (unsigned int i = 0; i < 3; i++)
	{
		if (m_Buttons[i]->IsClicked())
			Load::LoadGame(i);
	}

	//Return to MainMenu
	if (m_Buttons[3]->IsClicked())
	{
		SetScene(SceneType::MAINMENU);
	}
}

void TowerDefense::LoadMenu::OnSwitch()
{

}