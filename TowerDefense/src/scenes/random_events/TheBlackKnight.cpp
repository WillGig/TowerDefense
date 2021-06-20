#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"
#include "scenes/Base.h"

TowerDefense::TheBlackKnight::TheBlackKnight()
	:m_Image(std::make_unique<StaticImage>(180.0f, 350.0f, 300, 300, 0.0f, "events/BlackKnight")),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("I accept! (Gain Joust activity, lose 20 health)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("Search elsewhere knight. I have no time for games.", 400.0f, 100.0f, 12.0f, 0.0f))
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0, 1.0f);

	std::string text =
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

void TowerDefense::TheBlackKnight::Update()
{
	m_Button1->Update();
	if (m_Button1->IsClicked())
	{
		Base::AddBaseScene(std::make_shared<Joust>());
		Player::Get().ChangeHealth(-20);
		m_Exit = true;
	}

	m_Button2->Update();
	if (m_Button2->IsClicked())
	{
		m_Exit = true;
	}
}