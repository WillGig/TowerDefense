#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"
#include "scenes/Base.h"

TowerDefense::TheBlackKnight::TheBlackKnight()
	:m_Choice(0), 
	m_Image(std::make_unique<StaticImage>(180.0f, 350.0f, 300, 300, 0.0f, "events/BlackKnight")),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("I accept! (Gain Joust activity)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("I am only here to rest in peace (Heal 20 HP)", 400.0f, 100.0f, 12.0f, 0.0f))
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0, 1.0f);

	std::string text =
		"You come across a stream with a bridge over it.\n"
		"A tall Knight wearing black armor approaches.\n\n"
		"\"I am in search of a worthy opponent.\n"
		"Do you accept my challenge?\"\n";

	m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 12.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::TheBlackKnight::Render()
{
	m_Image->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();
	m_Prompt->Render();
}

void TowerDefense::TheBlackKnight::RenderEnd()
{
	m_Image->Render();
	m_Prompt->Render();
}

void TowerDefense::TheBlackKnight::OnEndSwitch()
{
	if (m_Choice == 1)
	{
		std::string text =
			"\"I will prepare. We shall fight at dawn.\"\n"
			"\"He rides off to get ready. \n"
			"You can now Joust at the base!\n";

		m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 12.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (m_Choice == 2)
	{
		std::string text =
			"He nods his head in understanding\n"
			"and rides off to continue his search.\n\n"
			"You rest for some time at the stream.\n";

		m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 12.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void TowerDefense::TheBlackKnight::Update()
{
	m_Button1->Update();
	if (m_Button1->IsClicked())
	{
		Base::AddBaseScene(std::make_shared<Joust>());

		m_Choice = 1;
		m_Exit = true;
	}

	m_Button2->Update();
	if (m_Button2->IsClicked())
	{
		Player::Get().ChangeHealth(20);

		m_Choice = 2;
		m_Exit = true;
	}
}