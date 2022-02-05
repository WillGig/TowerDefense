#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"

TowerDefense::LiterallySatan::LiterallySatan()
	:m_Choice(0), m_ShowingDemoInfo(false), 
	m_Image(std::make_unique<StaticImage>(200.0f, 350.0f, 300, 300, 0.0f, "events/LiterallySatan")),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("Burn them. (Add 3 flames to your deck.)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("Burn me. (Lose 30 HP)", 400.0f, 100.0f, 12.0f, 0.0f)),
	m_DemoCard(std::make_unique<Flames>())
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	std::string text =
		"You follow a series of winding passages\n"
		"until you enter a dark room with a man\n"
		"sitting in the corner.\n"
		"His face is red and his eyes are black.\n\n"
		"He smiles at you and his eyes light up.\n"
		"Burn.... burn... something must burn.\n"
		"He looks greedily at your cards.";

	m_Prompt = std::make_unique<Text>(text, 560.0f, 400.0f, 16.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_DemoCard->SetX(700.0f);
	m_DemoCard->SetY(150.0f);
}

void TowerDefense::LiterallySatan::Render()
{
	m_Image->Render();
	m_Prompt->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();

	if (m_Button1->IsSelected())
		m_DemoCard->Render();

	if (m_ShowingDemoInfo)
	{
		RenderFade(.9f);
		m_DemoCard->RenderCardDetails();
	}
}

void TowerDefense::LiterallySatan::RenderEnd()
{
	m_Image->Render();
	m_Prompt->Render();
}

void TowerDefense::LiterallySatan::OnEndSwitch()
{
	if (m_Choice == 1)
	{
		std::string text =
			"As the cards burn he rolls on\n"
			"the floor cackling.\n\n"
			"Time to leave...\n";

		m_Prompt = std::make_unique<Text>(text, 560.0f, 400.0f, 16.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (m_Choice == 2)
	{
		std::string text =
			"His eyes light up and he smiles.\n"
			"Fire leaps out from his hands and\n"
			"you feel the heat of the flames.\n\n"
			"After some time, the fire recedes\n"
			"and the smoke clear.\n"
			"The man is gone.\n";

		m_Prompt = std::make_unique<Text>(text, 560.0f, 400.0f, 16.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void TowerDefense::LiterallySatan::Update()
{
	if (m_ShowingDemoInfo)
	{
		if (Input::GetLeftMouseClickedAndSetFalse())
			m_ShowingDemoInfo = false;
		return;
	}

	if (m_Button1->IsSelected() && m_DemoCard->Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetRightMouseClickedAndSetFalse())
		m_ShowingDemoInfo = true;

	m_Button1->Update();
	m_Button2->Update();

	if (m_Button1->IsClicked())
	{
		for(int i = 0; i < 3; i++)
			Player::Get().AddToDeck(std::make_shared<Flames>());

		m_Choice = 1;
		m_Exit = true;
	}
	else if (m_Button2->IsClicked())
	{
		Player::Get().ChangeHealth(-30);

		m_Exit = true;
	}
}