#include "pch.h"
#include "CaveScene.h"
#include "core/Player.h"

TowerDefense::CaveBat::CaveBat()
	:m_Image(std::make_unique<StaticImage>(220.0f, 350.0f, 300, 300, 0.0f, "events/CaveBat")),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("Fight (-1 HP)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("Feed (-10 HP. Get the bat's blessing.)", 400.0f, 100.0f, 12.0f, 0.0f))
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	std::string text =
		"You see a bat. He looks\n"
		"happy, but hungry.\n"
		"He could be happier.\n\n"
		"He looks at you.\n";

	m_Prompt = std::make_unique<Text>(text, 550.0f, 400.0f, 16.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::CaveBat::Render()
{
	m_Image->Render();
	m_Prompt->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();
}

void TowerDefense::CaveBat::Update()
{
	m_Button1->Update();
	m_Button2->Update();

	if (m_Button1->IsClicked())
	{
		Player::Get().ChangeHealth(-1);
		m_Exit = true;
	}
	else if (m_Button2->IsClicked())
	{
		Player::Get().ChangeHealth(-10);
		//TODO: Add blessing of the bat artifact
		m_Exit = true;
	}
}