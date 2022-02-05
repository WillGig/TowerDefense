#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"

TowerDefense::CaveBat::CaveBat()
	:m_Choice(0), m_ShowingDemoInfo(false), 
	m_Image(std::make_unique<StaticImage>(220.0f, 350.0f, 300, 300, 0.0f, "events/CaveBat")),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("Fight (-1 HP)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("Feed (-10 HP. Get the bat's blessing.)", 400.0f, 100.0f, 12.0f, 0.0f)),
	m_DemoArtifact(std::make_unique<BlessingOfTheBat>())
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	std::string text =
		"You see a bat. He looks\n"
		"happy, but hungry.\n"
		"He could be happier.\n\n"
		"He looks at you.";

	m_Prompt = std::make_unique<Text>(text, 550.0f, 400.0f, 16.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_DemoArtifact->SetX(650.0f);
	m_DemoArtifact->SetY(100.0f);
}

void TowerDefense::CaveBat::Render()
{
	m_Image->Render();
	m_Prompt->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();

	if (m_Button2->IsSelected())
		m_DemoArtifact->Render();

	if (m_ShowingDemoInfo)
	{
		RenderFade(.9f);
		m_DemoArtifact->RenderArtifactDetails();
	}
}

void TowerDefense::CaveBat::RenderEnd()
{
	m_Image->Render();
	m_Prompt->Render();
}

void TowerDefense::CaveBat::OnEndSwitch()
{
	if (m_Choice == 1)
	{
		std::string text =
			"Swat!\n"
			"The bat is no more.\n\n"
			"Your hand stings a little,\n"
			"but it wasn't much of a fight";

		m_Prompt = std::make_unique<Text>(text, 550.0f, 400.0f, 16.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (m_Choice == 2)
	{
		std::string text =
			"You extend your arm and the\n"
			"bat flies over. With a \n"
			"chomp it bites in and starts\n"
			"lapping up blood.\n\n"
			"He looks happy.";

		m_Prompt = std::make_unique<Text>(text, 550.0f, 400.0f, 16.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void TowerDefense::CaveBat::Update()
{
	if (m_ShowingDemoInfo)
	{
		if (Input::GetLeftMouseClickedAndSetFalse())
			m_ShowingDemoInfo = false;
		return;
	}

	if (m_Button2->IsSelected() && m_DemoArtifact->Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetRightMouseClickedAndSetFalse())
		m_ShowingDemoInfo = true;

	m_Button1->Update();
	m_Button2->Update();

	if (m_Button1->IsClicked())
	{
		Player::Get().ChangeHealth(-1);

		m_Choice = 1;
		m_Exit = true;
	}
	else if (m_Button2->IsClicked())
	{
		Player::Get().ChangeHealth(-10);
		Player::Get().AddToArtifacts(std::make_shared<BlessingOfTheBat>());

		m_Choice = 2;
		m_Exit = true;
	}
}