#include "pch.h"
#include "NewGameMenu.h"
#include "TowerDefense.h"
#include "core/SaveLoad.h"
#include "Combat.h"
#include "Base.h"
#include "core/Player.h"

TowerDefense::NewGameMenu::NewGameMenu()
	:m_Confirming(false), m_ConfirmingSlot(-1), m_Title(std::make_unique<Text>("New Game", 400.0f, 450.0f, 40.0f, 0.0f)),
	m_Save1Info(), m_Save2Info(), m_Save3Info(), 
	m_ConfirmText(std::make_unique<Text>("Overwrite save data?", 400.0f, 400.0f, 20.0f, 0.0f)),
	m_Fade(std::make_unique<Rectangle>(400.0f, 300.0f, 800.0f, 600.0f))
{
	m_Title->SetColor(0.7f, 0.7f, 0.7f, 1.0f);
	m_ConfirmText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Fade->SetColor(0.0f, 0.0f, 0.0f, 0.9f);
	m_Buttons =
	{
		std::make_unique<Button>(400.0f, 350.0f, 200, 50, "slotEmpty"),
		std::make_unique<Button>(400.0f, 300.0f, 200, 50, "slotEmpty"),
		std::make_unique<Button>(400.0f, 250.0f, 200, 50, "slotEmpty"),
		std::make_unique<Button>(400.0f, 150.0f, 200, 50, "backButton"),
		std::make_unique<Button>(400.0f, 325.0f, 200, 50, "menuConfirm"),
		std::make_unique<Button>(400.0f, 275.0f, 200, 50, "menuCancel")
	};
}

void TowerDefense::NewGameMenu::Render()
{
	m_Title->Render();
	for (unsigned int i = 0; i < 4; i++)
		m_Buttons[i]->Render();

	if (m_Save1Info->GetMessage() != "")
		m_Save1Info->Render();
	if (m_Save2Info->GetMessage() != "")
		m_Save2Info->Render();
	if (m_Save3Info->GetMessage() != "")
		m_Save3Info->Render();

	if (m_Confirming)
	{
		m_Fade->Render();
		m_ConfirmText->Render();
		m_Buttons[4]->Render();
		m_Buttons[5]->Render();
	}
}

void TowerDefense::NewGameMenu::Update()
{
	if (m_Confirming)
	{
		//Confirm
		m_Buttons[4]->Update();
		if (m_Buttons[4]->IsClicked())
		{
			Random::Get().NewSeed();
			ResetDay();
			Combat::GenerateFights();
			Base::Reset();
			Player::Get().Reset();
			Base::SaveSlot = m_ConfirmingSlot;
			SetScene(SceneType::BASE);
		}
		//Cancel
		m_Buttons[5]->Update();
		if (m_Buttons[5]->IsClicked())
		{
			m_Confirming = false;
		}
		return;
	}

	for (unsigned int i = 0; i < 4; i++)
		m_Buttons[i]->Update();

	//Save Slots
	for (unsigned int i = 0; i < 3; i++)
	{
		if (m_Buttons[i]->IsClicked())
		{
			//Empty Slot
			if (m_Buttons[i]->GetImageName() == "slotEmpty")
			{
				Random::Get().NewSeed();
				ResetDay();
				Combat::GenerateFights();
				Base::Reset();
				Player::Get().Reset();
				Base::SaveSlot = i + 1;
				SetScene(SceneType::BASE);
			}
			//Occupied Slot
			else
			{
				m_Confirming = true;
				m_ConfirmingSlot = i + 1;
			}
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