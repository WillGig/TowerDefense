#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"
#include "cards/HeroCard.h"
#include "Towers/Bard.h"
#include "cards/quirks/Quirk.h"

TowerDefense::WanderingBard::WanderingBard()
	:m_Image(std::make_unique<StaticImage>(180.0f, 350.0f, 300, 300, 0.0f, "events/Bard")),
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
}

void TowerDefense::WanderingBard::Render()
{
	m_Image->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();
	m_Prompt->Render();
}

void TowerDefense::WanderingBard::Update()
{
	Player& player = Player::Get();
	if(player.GetResource(Resource::GOLD) > 299)
		m_Button1->Update();
	if (m_Button1->IsClicked())
	{
		auto quirks = std::make_shared<std::vector<std::shared_ptr<Quirk::Quirk>>>();
		quirks->push_back(std::make_shared<Quirk::Human>());
		quirks->push_back(std::make_shared<Quirk::Veteran>());
		quirks->push_back(std::make_shared<Quirk::Explorer>());
		quirks->push_back(std::make_shared<Quirk::Nearsighted>());

		player.AddToDeck(std::make_shared<HeroCard>("Hoid", "Class:  Bard\nRace:  Human\nVeteran\nExplorer\nNear Sighted\n", 50, "hoid", std::make_shared<Tower::Bard>(), quirks));
		player.ChangeResource(-300, Resource::GOLD);
		m_Exit = true;
	}

	m_Button2->Update();
	if (m_Button2->IsClicked())
	{
		m_Exit = true;
	}
}