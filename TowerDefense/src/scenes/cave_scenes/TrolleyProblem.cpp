#include "pch.h"
#include "CaveScene.h"
#include "core/Player.h"

TowerDefense::TrolleyProblem::TrolleyProblem()
	:m_Image(std::make_unique<StaticImage>(400.0f, 425.0f, 600, 300, 0.0f, "events/TrolleyProblem")),
	m_Button1(std::make_unique<Button>(400.0f, 175.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 125.0f, 600, 50, "eventButton")),
	m_Button3(std::make_unique<Button>(400.0f, 75.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("Do nothing (The baby dies)", 400.0f, 175.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("Switch the track (The puppies AND the criminals die)", 400.0f, 125.0f, 12.0f, 0.0f)),
	m_Text3(std::make_unique<Text>("This has nothing to do with this game!? (-1 HP)", 400.0f, 75.0f, 12.0f, 0.0f))
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text3->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	std::string text =
		"In the caves you find a room a track that splits in two. Down the track comes\n"
		"a truck full of puppies. It is headed towards a baby lying on the track. In \n"
		"front of you, there is a lever that will switch the track. On the other track are\n"
		"3 criminals in a cage. You know that hitting them would also kill the puppies.\n";

	m_Prompt = std::make_unique<Text>(text, 400.0f, 300.0f, 12.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::TrolleyProblem::Render()
{
	m_Image->Render();
	m_Prompt->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Button3->Render();
	m_Text1->Render();
	m_Text2->Render();
	m_Text3->Render();
}

void TowerDefense::TrolleyProblem::Update()
{
	m_Button1->Update();
	m_Button2->Update();
	m_Button3->Update();

	if (m_Button1->IsClicked())
		m_Exit = true;
	else if (m_Button2->IsClicked())
		m_Exit = true;
	else if(m_Button3->IsClicked())
	{ 
		Player::Get().ChangeHealth(-1);
		m_Exit = true;
	}
}