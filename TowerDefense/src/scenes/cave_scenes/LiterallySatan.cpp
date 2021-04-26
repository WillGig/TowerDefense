#include "pch.h"
#include "CaveScene.h"
#include "core/Player.h"
#include "cards/curses/Curses.h"

TowerDefense::LiterallySatan::LiterallySatan()
	:m_Image(std::make_unique<StaticImage>(200.0f, 350.0f, 300, 300, 0.0f, "LiterallySatan")),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("Burn it. (Add 3 burns to your deck.)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("Burn me. (Lose 30 HP)", 400.0f, 100.0f, 12.0f, 0.0f))
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	std::string text =
		"You follow a series of winding passages\n"
		"until you enter a dark room with a man\n"
		"sitting in the corner.\n"
		"His face is red and his eyes are black.\n\n"
		"He smiles at you and his eyes light up.\n"
		"Burn.....burn... something must burn.\n"
		"He looks greedily at your cards.";

	m_Prompt = std::make_unique<Text>(text, 560.0f, 450.0f, 16.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::LiterallySatan::Render()
{
	m_Image->Render();
	m_Prompt->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();
}

void TowerDefense::LiterallySatan::Update()
{
	m_Button1->Update();
	m_Button2->Update();

	if (m_Button1->IsClicked())
	{
		for(int i = 0; i < 3; i++)
			Player::Get().GetDeck()->AddCard(std::make_shared<Flames>());
		m_Exit = true;
	}
	else if (m_Button2->IsClicked())
	{
		Player::Get().ChangeHealth(-30);
		m_Exit = true;
	}
}