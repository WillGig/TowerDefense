#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"
#include "cards/HeroCard.h"
#include "Towers/Bard.h"
#include "cards/quirks/Quirk.h"

TowerDefense::WanderingBard::WanderingBard()
	:m_ShowingDemoInfo(false), m_Image(std::make_unique<StaticImage>(180.0f, 350.0f, 300, 300, 0.0f, "events/Bard")),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("Play it! (Lose 300 gold, gain Hoid the Bard)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("I have no time for songs, minstrel. Be on your way.", 400.0f, 100.0f, 12.0f, 0.0f))
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0, 1.0f);

	std::string text =
		"An elegant man holding a flute walks up to you.\n"
		"\"We could be friends.\n"
		"Want to hear a tune?\n"
		"It will only cost a little coin.\"\n";

	m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 12.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	auto quirks = std::make_shared<std::vector<std::shared_ptr<Quirk::Quirk>>>();
	quirks->push_back(std::make_shared<Quirk::Human>());
	quirks->push_back(std::make_shared<Quirk::Sage>());
	quirks->push_back(std::make_shared<Quirk::Explorer>());
	quirks->push_back(std::make_shared<Quirk::Nearsighted>());
	m_DemoCard = std::make_unique<HeroCard>("Hoid", "Class:  Bard\nRace:  Human\nSage\nExplorer\nNear Sighted\n", 50, "hoid", std::make_shared<Tower::Bard>(), quirks);

	m_DemoCard->SetX(700.0f);
	m_DemoCard->SetY(150.0f);
}

void TowerDefense::WanderingBard::Render()
{
	m_Image->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();
	m_Prompt->Render();

	if (m_Button1->IsSelected())
		m_DemoCard->Render();

	if (m_ShowingDemoInfo)
	{
		RenderFade(.9f);
		m_DemoCard->RenderCardDetails();
	}
}

void TowerDefense::WanderingBard::RenderEnd()
{
	m_Image->Render();
	m_Prompt->Render();
}

void TowerDefense::WanderingBard::Update()
{
	if (m_ShowingDemoInfo)
	{
		if (Input::GetLeftMouseClickedAndSetFalse())
			m_ShowingDemoInfo = false;
		return;
	}

	if (m_Button1->IsSelected() && m_DemoCard->Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetRightMouseClickedAndSetFalse())
		m_ShowingDemoInfo = true;

	Player& player = Player::Get();
	if(player.GetResource(Resource::GOLD) > 299)
		m_Button1->Update();
	if (m_Button1->IsClicked())
	{
		auto quirks = std::make_shared<std::vector<std::shared_ptr<Quirk::Quirk>>>();
		quirks->push_back(std::make_shared<Quirk::Human>());
		quirks->push_back(std::make_shared<Quirk::Sage>());
		quirks->push_back(std::make_shared<Quirk::Explorer>());
		quirks->push_back(std::make_shared<Quirk::Nearsighted>());

		player.AddToDeck(std::make_shared<HeroCard>("Hoid", "Class:  Bard\nRace:  Human\nSage\nExplorer\nNear Sighted\n", 50, "hoid", std::make_shared<Tower::Bard>(), quirks));
		player.ChangeResource(-300, Resource::GOLD);

		std::string text =
			"You gain hoid the bard!\n";

		m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 12.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

		m_Exit = true;
	}

	m_Button2->Update();
	if (m_Button2->IsClicked())
	{
		std::string text =
			"\"I see... \"\n"
			"With a dip of his head\n"
			"and a turn of his heel,\n"
			"he turns away and leaves.\n";

		m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 12.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

		m_Exit = true;
	}
}