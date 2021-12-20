#include "pch.h"
#include "NewGameMenu.h"
#include "TowerDefense.h"
#include "core/SaveLoad.h"
#include "Combat.h"
#include "Base.h"
#include "core/Player.h"

TowerDefense::NewGameMenu::NewGameMenu()
	:m_Title(std::make_unique<Text>("New Game", 400.0f, 450.0f, 40.0f, 0.0f)),
	m_Save1Info(), m_Save2Info(), m_Save3Info()
{
	m_Title->SetColor(0.7f, 0.7f, 0.7f, 1.0f);
	m_Buttons =
	{
		std::make_unique<Button>(400.0f, 350.0f, 200, 50, "slotEmpty"),
		std::make_unique<Button>(400.0f, 300.0f, 200, 50, "slotEmpty"),
		std::make_unique<Button>(400.0f, 250.0f, 200, 50, "slotEmpty"),
		std::make_unique<Button>(400.0f, 150.0f, 200, 50, "backButton")
	};
}

void TowerDefense::NewGameMenu::Render()
{
	m_Title->Render();
	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->Render();

	if (m_Save1Info->GetMessage() != "")
		m_Save1Info->Render();
	if (m_Save2Info->GetMessage() != "")
		m_Save2Info->Render();
	if (m_Save3Info->GetMessage() != "")
		m_Save3Info->Render();
}

void TowerDefense::NewGameMenu::Update()
{
	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->Update();

	//Save Slots
	for (unsigned int i = 0; i < 3; i++)
	{
		if (m_Buttons[i]->IsClicked())
		{
			Random::Get().NewSeed();
			ResetDay();
			Combat::GenerateFights();
			Base::Reset();
			Player::Get().Reset();
			Base::SaveSlot = i+1;
			SetScene(SceneType::BASE);
		}
	}

	//Return to MainMenu
	if (m_Buttons[3]->IsClicked())
	{
		SetScene(SceneType::MAINMENU);
	}
}

void TowerDefense::NewGameMenu::OnSwitch()
{
	std::ifstream save1("res/saves/save1.dat");
	if (save1.is_open())
	{
		std::string line;
		std::getline(save1, line);
		std::string day = line;
		std::getline(save1, line);
		std::string date = line;

		m_Save1Info = std::make_unique<Text>("Day: " + day + "\n" + date, 400.0f, 350.0f, 10.0f, 200.0f);
		m_Save1Info->SetColor(0.7f, 0.7f, 0.7f, 1.0f);
		m_Buttons[0]->SetImages("slotFull");
	}
	else
	{
		m_Save1Info = std::make_unique<Text>("", 400.0f, 350.0f, 10.0f, 200.0f);
		m_Buttons[0]->SetImages("slotEmpty");
	}	
	save1.close();

	std::ifstream save2("res/saves/save2.dat");
	if (save2.is_open())
	{
		std::string line;
		std::getline(save2, line);
		std::string day = line;
		std::getline(save2, line);
		std::string date = line;

		m_Save2Info = std::make_unique<Text>("Day: " + day + "\n" + date, 400.0f, 300.0f, 10.0f, 200.0f);
		m_Save2Info->SetColor(0.7f, 0.7f, 0.7f, 1.0f);
		m_Buttons[1]->SetImages("slotFull");
	}
	else
	{
		m_Save2Info = std::make_unique<Text>("", 400.0f, 300.0f, 10.0f, 200.0f);
		m_Buttons[1]->SetImages("slotEmpty");
	}
	save2.close();

	std::ifstream save3("res/saves/save3.dat");
	if (save3.is_open())
	{
		std::string line;
		std::getline(save3, line);
		std::string day = line;
		std::getline(save3, line);
		std::string date = line;

		m_Save3Info = std::make_unique<Text>("Day: " + day + "\n" + date, 400.0f, 250.0f, 10.0f, 200.0f);
		m_Save3Info->SetColor(0.7f, 0.7f, 0.7f, 1.0f);
		m_Buttons[2]->SetImages("slotFull");
	}
	else
	{
		m_Save3Info = std::make_unique<Text>("", 400.0f, 250.0f, 10.0f, 200.0f);
		m_Buttons[2]->SetImages("slotEmpty");
	}
	save3.close();
}