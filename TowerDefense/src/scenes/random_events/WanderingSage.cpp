#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"
#include "cards/HeroCard.h"
#include "Towers/Wizard.h"
#include "cards/quirks/Quirk.h"

TowerDefense::WanderingSage::WanderingSage()
	:m_Image(std::make_unique<StaticImage>(180.0f, 350.0f, 300, 300, 0.0f, "events/Sage")),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("Show me. (Lose all wood, gain Heath the Wizard)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("No this stick is very important to me.", 400.0f, 100.0f, 12.0f, 0.0f))
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0, 1.0f);

	std::string text =
		"A strange man walks up to you.\n"
		"\"We could be friends.\n"
		"Want to see a magic trick?\n"
		"I can make this stick disappear.\"\n";

	m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 16.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::WanderingSage::Render()
{
	m_Image->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();
	m_Prompt->Render();
}

void TowerDefense::WanderingSage::Update()
{
	m_Button1->Update();
	if (m_Button1->IsClicked())
	{
		auto quirks = std::make_shared<std::vector<std::shared_ptr<Quirk::Quirk>>>();
		quirks->push_back(std::make_shared<Quirk::Human>());
		quirks->push_back(std::make_shared<Quirk::Veteran>());
		quirks->push_back(std::make_shared<Quirk::JustLucky>());
		quirks->push_back(std::make_shared<Quirk::Nearsighted>());

		Player& player = Player::Get();

		player.AddToDeck(std::make_shared<HeroCard>("Heath", "Class:  Wizard\nRace:  Human\nVeteran\nJust Lucky\nNear Sighted\n", 100, "heath", std::make_shared<Tower::Wizard>(), quirks));
		player.ChangeResource(-player.GetResource(Resource::WOOD), Resource::WOOD);
		m_Exit = true;
	}

	m_Button2->Update();
	if (m_Button2->IsClicked())
	{
		m_Exit = true;
	}
}