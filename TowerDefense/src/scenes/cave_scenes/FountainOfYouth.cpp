#include "pch.h"
#include "CaveScene.h"
#include "core/Player.h"

TowerDefense::FountainOfYouth::FountainOfYouth()
	:m_prompt(std::make_unique<StaticImage>(400.0f, 350.0f, 600, 400, 0.0f, "FountainOfYouth")),
	m_Button1(std::make_unique<Button>(600, 50, 400.0f, 200.0f, "eventButton")),
	m_Button2(std::make_unique<Button>(600, 50, 400.0f, 150.0f, "eventButton")),
	m_Text1(std::make_unique<Text>("Drink (Heal to Full HP)", 400.0f, 200.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("Bathe (Gain 10 max HP)", 400.0f, 150.0f, 12.0f, 0.0f))
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::FountainOfYouth::Render()
{
	m_prompt->Render();
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