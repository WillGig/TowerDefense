#include "pch.h"
#include "LoadMenu.h"
#include "TowerDefense.h"
#include "core/SaveLoad.h"

TowerDefense::LoadMenu::LoadMenu()
	:m_Title(std::make_unique<Text>("Load Game", 400.0f, 450.0f, 40.0f, 0.0f)),
	m_Save1Info(), m_Save2Info(), m_Save3Info(),
	m_ConfirmText(std::make_unique<Text>("Delete Save File?", 400.0f, 400.0f, 20.0f, 0.0f)),
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
		std::make_unique<Button>(530.0f, 350.0f, 32, 32, "xButton"),
		std::make_unique<Button>(530.0f, 300.0f, 32, 32, "xButton"),
		std::make_unique<Button>(530.0f, 250.0f, 32, 32, "xButton"),
		std::make_unique<Button>(400.0f, 325.0f, 200, 50, "menuConfirm"),
		std::make_unique<Button>(400.0f, 275.0f, 200, 50, "menuCancel")
	};
}

void TowerDefense::LoadMenu::Render()
{
	m_Title->Render();
	for (unsigned int i = 0; i < 4; i++)
		m_Buttons[i]->Render();

	if (m_Save1Info->GetMessage() != "")
	{
		m_Save1Info->Render();
		m_Buttons[4]->Render();
	}
	if (m_Save2Info->GetMessage() != "")
	{
		m_Save2Info->Render();
		m_Buttons[5]->Render();
	}
	if (m_Save3Info->GetMessage() != "")
	{
		m_Save3Info->Render();
		m_Buttons[6]->Render();
	}

	if (m_Confirming)
	{
		m_Fade->Render();
		m_ConfirmText->Render();
		m_Buttons[7]->Render();
		m_Buttons[8]->Render();
	}
}

void TowerDefense::LoadMenu::Update()
{
	if (m_Confirming)
	{
		//Confirm
		m_Buttons[7]->Update();
		if (m_Buttons[7]->IsClicked())
		{
			//Delete save file
			std::string file = "res/saves/save" + std::to_string(m_ConfirmingSlot + 1) + ".dat";
			if (std::remove(file.c_str()) != 0)
				std::cout << "Error deleting save file";

			//Reset Button Iamges and Info
			m_Buttons[m_ConfirmingSlot]->SetImages("slotEmpty");
			if (m_ConfirmingSlot == 0)
				m_Save1Info = std::make_unique<Text>("", 400.0f, 400.0f, 10.0f, 200.0f);
			else if (m_ConfirmingSlot == 1)
				m_Save2Info = std::make_unique<Text>("", 400.0f, 350.0f, 10.0f, 200.0f);
			else if (m_ConfirmingSlot == 2)
				m_Save3Info = std::make_unique<Text>("", 400.0f, 300.0f, 10.0f, 200.0f);

			m_Confirming = false;
			m_Buttons[m_ConfirmingSlot + 4]->Update();
		}
		//Cancel
		m_Buttons[8]->Update();
		if (m_Buttons[8]->IsClicked())
			m_Confirming = false;
		return;
	}

	for (unsigned int i = 0; i < 3; i++)
		if (m_Buttons[i]->GetImageName() != "slotEmpty")
		{
			m_Buttons[i]->Update();		//Save slot
			m_Buttons[i + 4]->Update(); //X button
		}
	m_Buttons[3]->Update(); //Back button

	//Save Slots
	for (unsigned int i = 0; i < 3; i++)
	{
		if (m_Buttons[i]->IsClicked()) //Slot
			Load::LoadGame(i+1);
		else if (m_Buttons[i + 4]->IsClicked()) //X Button
		{
			m_Confirming = true;
			m_ConfirmingSlot = i;
		}
	}

	//Return to MainMenu
	if (m_Buttons[3]->IsClicked())
		SetScene(SceneType::MAINMENU);
}

void TowerDefense::LoadMenu::OnSwitch()
{
	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->SetSelected(false);

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
		m_Save3Info = std::make_unique<Text>("", 400.0f, 300.0f, 10.0f, 200.0f);
		m_Buttons[2]->SetImages("slotEmpty");
	}
	save3.close();
}