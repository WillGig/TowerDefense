#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"
#include "cards/curses/Curses.h"

TowerDefense::FrogPrince::FrogPrince()
	:m_Choice(0), m_ShowingDemoCardInfo(false), m_ShowingDemoArtifactInfo(false),
	m_Image(std::make_unique<StaticImage>(180.0f, 350.0f, 300, 300, 0.0f, "events/Frog")),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("Kiss the Frog. (50% Prince, 50% Frog)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("Sell the talking frog. +200 Gold", 400.0f, 100.0f, 12.0f, 0.0f)),
	m_DemoArtifact(std::make_unique<Prince>()),
	m_DemoCard(std::make_unique<Frog>())
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

	m_DemoArtifact->SetX(200.0f);
	m_DemoArtifact->SetY(150.0f);

	m_DemoCard->SetX(650.0f);
	m_DemoCard->SetY(150.0f);
}

void TowerDefense::FrogPrince::Render()
{
	m_Image->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();
	m_Prompt->Render();

	if (m_Button1->IsSelected())
	{
		m_DemoArtifact->Render();
		m_DemoCard->Render();
	}

	if (m_ShowingDemoCardInfo)
	{
		RenderFade(.9f);
		m_DemoCard->RenderCardDetails();
	}
	else if(m_ShowingDemoArtifactInfo)
	{
		RenderFade(.9f);
		m_DemoArtifact->RenderArtifactDetails();
	}
}

void TowerDefense::FrogPrince::RenderEnd()
{
	m_Image->Render();
	m_Prompt->Render();
}

void TowerDefense::FrogPrince::OnEndSwitch()
{
	if (m_Choice == 1)
	{
		std::string text;

		if (Random::GetFloat() > 0.5f)
		{
			Player::Get().AddToArtifacts(std::make_shared<Prince>());
			text =
				"A huge cloud of smoke appears.\n"
				"Eventually the smoke disapates and...\n"
				"a prince appears!\n\n"
				"\"Happy to be of service, my friend.\"\n";
		}
		else
		{
			Player::Get().AddToDeck(std::make_shared<Frog>());
			text =
				"A huge cloud of smoke appears.\n"
				"Eventually the smoke disapates and...\n"
				"The frog is still there.\n\n"
				"\"Did it work? Am I a prince now?\"\n";
		}

		m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 16.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (m_Choice == 2)
	{
		std::string text =
			"It doesn't take long to\n"
			"find a buyer. \n\n"
			"The frog croaks sadly as\n"
			"he is taken away in chains.\n";

		m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 16.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void TowerDefense::FrogPrince::Update()
{
	if (m_ShowingDemoCardInfo)
	{
		if (Input::GetLeftMouseClickedAndSetFalse())
			m_ShowingDemoCardInfo = false;
		return;
	}
	else if (m_ShowingDemoArtifactInfo)
	{
		if (Input::GetLeftMouseClickedAndSetFalse())
			m_ShowingDemoArtifactInfo = false;
		return;
	}

	if (m_Button1->IsSelected())
	{
		if (m_DemoCard->Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetRightMouseClickedAndSetFalse())
			m_ShowingDemoCardInfo = true;
		else if (m_DemoArtifact->Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetRightMouseClickedAndSetFalse())
			m_ShowingDemoArtifactInfo = true;
	}

	m_Button1->Update();
	if (m_Button1->IsClicked())
	{
		m_Choice = 1;
		m_Exit = true;
	}

	m_Button2->Update();
	if (m_Button2->IsClicked())
	{
		Player::Get().ChangeResource(200, Resource::GOLD);

		m_Choice = 2;
		m_Exit = true;
	}
}