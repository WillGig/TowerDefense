#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"

TowerDefense::KnightsWhoSayNah::KnightsWhoSayNah()
	:m_Image(std::make_unique<Image>("events/KnightsWhoSayNah", 180.0f, 350.0f, 300, 300, 0.0f)),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Button3(std::make_unique<Button>(400.0f, 50.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("Give in to their demands (-300 Gold)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("They say Nah to you (-10hp)", 400.0f, 100.0f, 12.0f, 0.0f)),
	m_Text3(std::make_unique<Text>("Give Shrubbery (Recieve Blessed Hand grenade)", 400.0f, 50.0f, 12.0f, 0.0f))
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
	}
}

void TowerDefense::KnightsWhoSayNah::Update()
{
	m_Button1->Update();
	if (m_Button1->IsClicked())
	{
		Player::Get().ChangeResource(-300, Resource::GOLD);
		m_Exit = true;
	}

	m_Button2->Update();
	if (m_Button2->IsClicked())
	{
		Player::Get().ChangeHealth(-10);
		m_Exit = true;
	}

	if (Player::Get().HasArtifact("Shrubbery"))
	{
		m_Button3->Update();
		if (m_Button3->IsClicked())
		{
			Player::Get().AddToArtifacts(std::make_shared<BlessedHandGrenade>());
			Player::Get().RemoveFromArtifacts("Shrubbery");
			m_Exit = true;
		}
	}
}