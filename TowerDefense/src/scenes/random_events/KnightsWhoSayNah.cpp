#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"

TowerDefense::KnightsWhoSayNah::KnightsWhoSayNah()
	:m_ShowingDemoInfo(false), m_Image(std::make_unique<Image>("events/KnightsWhoSayNah", 180.0f, 350.0f, 300, 300, 0.0f)),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Button3(std::make_unique<Button>(400.0f, 50.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("Give in to their demands (-300 Gold)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("They say Nah to you (-10hp)", 400.0f, 100.0f, 12.0f, 0.0f)),
	m_Text3(std::make_unique<Text>("Give Shrubbery (Recieve Blessed Hand grenade)", 400.0f, 50.0f, 12.0f, 0.0f)),
	m_DemoArtifact(std::make_unique<BlessedHandGrenade>())
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0, 1.0f);
	m_Text3->SetColor(1.0f, 1.0f, 1.0, 1.0f);

	std::string text =
		"\"We are the Knights who say Nah! \n\n"
		"Nah!\n\n"
		"Give in to our demands or we will say \n"
		"Nah to you again!\n\n"
		"Now give us 300 Gold!\"\n";

	m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 16.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_DemoArtifact->SetX(650.0f);
	m_DemoArtifact->SetY(50.0f);
}

void TowerDefense::KnightsWhoSayNah::Render()
{
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();
	m_Image->Render();
	m_Prompt->Render();

	if (Player::Get().HasArtifact("Shrubbery"))
	{
		m_Button3->Render();
		m_Text3->Render();
		if (m_Button3->IsSelected())
			m_DemoArtifact->Render();
	}

	if (m_ShowingDemoInfo)
	{
		RenderFade(.9f);
		m_DemoArtifact->RenderArtifactDetails();
	}
}

void TowerDefense::KnightsWhoSayNah::RenderEnd()
{
	m_Image->Render();
	m_Prompt->Render();
}
void TowerDefense::KnightsWhoSayNah::Update()
{
	if (m_ShowingDemoInfo)
	{
		if (Input::GetLeftMouseClickedAndSetFalse())
			m_ShowingDemoInfo = false;
		return;
	}

	if (m_Button3->IsSelected() && m_DemoArtifact->Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetRightMouseClickedAndSetFalse())
		m_ShowingDemoInfo = true;

	m_Button1->Update();
	if (m_Button1->IsClicked())
	{
		Player::Get().ChangeResource(-300, Resource::GOLD);

		std::string text =
			"\"A wise choice!\n"
			"Move along now.\"";

		m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 16.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

		m_Exit = true;
	}

	m_Button2->Update();
	if (m_Button2->IsClicked())
	{
		Player::Get().ChangeHealth(-10);

		std::string text =
			"\"Nah! Nah! Nah! Nah! Nah!\n"
			"Nah! Nah! Nah! Nah!\"";

		m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 16.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

		m_Exit = true;
	}

	if (Player::Get().HasArtifact("Shrubbery"))
	{
		m_Button3->Update();
		if (m_Button3->IsClicked())
		{
			Player::Get().AddToArtifacts(std::make_shared<BlessedHandGrenade>());
			Player::Get().RemoveFromArtifacts("Shrubbery");

			std::string text =
				"\"Oooh it looks nice.\n\n"
				"All of the Knights begin to crowd"
				"around and  inspect the shruberry\n\n"
				"After a while the leader comes up\n"
				"holding a box. \n\n"
				"\"We thank you for the shruberry\n"
				"Take this: you may need it";

			m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 16.0f, 0.0f);
			m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

			m_Exit = true;
		}
	}
}