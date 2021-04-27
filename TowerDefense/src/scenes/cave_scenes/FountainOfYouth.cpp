#include "pch.h"
#include "CaveScene.h"
#include "core/Player.h"

TowerDefense::FountainOfYouth::FountainOfYouth()
	:m_Image(std::make_unique<StaticImage>(230.0f, 350.0f, 300, 300, 0.0f, "events/FountainOfYouth")),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("Drink (Heal to Full HP)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("Bathe (Gain 10 max HP)", 400.0f, 100.0f, 12.0f, 0.0f))
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	std::string text =
		"You come across a golden\n"
		"fountain with clear crystal\n"
		"water pouring from it.\n\n"
		"The Fountain exudes life\n"
		"and smells of mint.\n";

	m_Prompt = std::make_unique<Text>(text, 550.0f, 450.0f, 18.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::FountainOfYouth::Render()
{
	m_Image->Render();
	m_Prompt->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();
}

void TowerDefense::FountainOfYouth::Update()
{
	m_Button1->Update();
	m_Button2->Update();

	if (m_Button1->IsClicked())
	{
		Player& player = Player::Get();
		player.ChangeHealth(player.GetMaxHealth()-player.GetHealth());
		m_Exit = true;
	}
	else if (m_Button2->IsClicked())
	{
		Player::Get().ChangeMaxHealth(10);
		m_Exit = true;
	}
}