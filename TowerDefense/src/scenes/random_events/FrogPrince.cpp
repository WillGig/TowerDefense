#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"
#include "cards/curses/Curses.h"

TowerDefense::FrogPrince::FrogPrince()
	:m_Image(std::make_unique<StaticImage>(180.0f, 350.0f, 300, 300, 0.0f, "events/Frog")),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("Kiss the Frog. (50% obtain a Prince, 50% obtain a Frog)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("Sell the talking frog. +200 Gold", 400.0f, 100.0f, 12.0f, 0.0f))
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0, 1.0f);

	std::string text =
		"A frog hops up to you.\n"
		"It tells you its name is Eric\n"
		"and it used to be a prince.\n\n"
		"\"If you kiss me, I'll turn human again!\"\n";

	m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 16.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::FrogPrince::Render()
{
	m_Image->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();
	m_Prompt->Render();
}

void TowerDefense::FrogPrince::Update()
{
	m_Button1->Update();
	if (m_Button1->IsClicked())
	{
		if (Random::GetFloat() > 0.5f)
			Player::Get().AddToArtifacts(std::make_shared<Prince>());
		else
			Player::Get().AddToDeck(std::make_shared<Frog>());
		m_Exit = true;
	}

	m_Button2->Update();
	if (m_Button2->IsClicked())
	{
		Player::Get().ChangeResource(200, Resource::GOLD);
		m_Exit = true;
	}
}