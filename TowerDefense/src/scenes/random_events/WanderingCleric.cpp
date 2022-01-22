#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"
#include "cards/HeroCard.h"
#include "Towers/Cleric.h"
#include "cards/quirks/Quirk.h"

TowerDefense::WanderingCleric::WanderingCleric()
	:m_Image(std::make_unique<StaticImage>(180.0f, 350.0f, 300, 300, 0.0f, "events/Cleric")),
	m_Button1(std::make_unique<Button>(400.0f, 150.0f, 600, 50, "eventButton")),
	m_Button2(std::make_unique<Button>(400.0f, 100.0f, 600, 50, "eventButton")),
	m_Text1(std::make_unique<Text>("What is mine, is theirs. (Lose all your wheat, gain Aramis the cleric)", 400.0f, 150.0f, 12.0f, 0.0f)),
	m_Text2(std::make_unique<Text>("Are there no prisons? Are there no workhouses?", 400.0f, 100.0f, 12.0f, 0.0f))
{
	m_Text1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Text2->SetColor(1.0f, 1.0f, 1.0, 1.0f);

	std::string text =
		"A withered old man hobbles up to you.\n"
		"\"Alms for the poor?\n"
		"There are those who will starve here.\n"
		"Can you spare them some food?\"\n";

	m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 12.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	auto quirks = std::make_shared<std::vector<std::shared_ptr<Quirk::Quirk>>>();
	quirks->push_back(std::make_shared<Quirk::Human>());
	quirks->push_back(std::make_shared<Quirk::Sage>());
	quirks->push_back(std::make_shared<Quirk::Veteran>());
	quirks->push_back(std::make_shared<Quirk::Nearsighted>());
	m_DemoCard = std::make_unique<HeroCard>("Aramis", "Class:  Cleric\nRace:  Human\nSage\nVeteran\nNear Sighted\n", 50, "aramis", std::make_shared<Tower::Cleric>(), quirks);

	m_DemoCard->SetX(700.0f);
	m_DemoCard->SetY(150.0f);
}

void TowerDefense::WanderingCleric::Render()
{
	m_Image->Render();
	m_Button1->Render();
	m_Button2->Render();
	m_Text1->Render();
	m_Text2->Render();
	m_Prompt->Render();

	if (m_Button1->IsSelected())
		m_DemoCard->Render();
}

void TowerDefense::WanderingCleric::RenderEnd()
{
	m_Image->Render();
	m_Prompt->Render();
}

void TowerDefense::WanderingCleric::Update()
{
	m_Button1->Update();
	if (m_Button1->IsClicked())
	{
		auto quirks = std::make_shared<std::vector<std::shared_ptr<Quirk::Quirk>>>();
		quirks->push_back(std::make_shared<Quirk::Human>());
		quirks->push_back(std::make_shared<Quirk::Sage>());
		quirks->push_back(std::make_shared<Quirk::Veteran>());
		quirks->push_back(std::make_shared<Quirk::Nearsighted>());

		Player& player = Player::Get();
		player.AddToDeck(std::make_shared<HeroCard>("Aramis", "Class:  Cleric\nRace:  Human\nSage\nVeteran\nNear Sighted\n", 50, "aramis", std::make_shared<Tower::Cleric>(), quirks));
		player.ChangeResource(-player.GetResource(Resource::WHEAT), Resource::WHEAT);
		
		std::string text =
			"All of your wheat has been given away.\n"
			"You gain Aramis the cleric!";

		m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 12.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		
		m_Exit = true;
	}

	m_Button2->Update();
	if (m_Button2->IsClicked())
	{
		std::string text =
			"The man gives you a disgusted look.\n\n"
			"He spits on the ground at your feet,\n"
			"turns, and leaves.\n";

		m_Prompt = std::make_unique<Text>(text, 560.0f, 370.0f, 12.0f, 0.0f);
		m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

		m_Exit = true;
	}
}