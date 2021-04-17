#include "pch.h"
#include "Base.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "cards/HeroCard.h"

TowerDefense::Base::Base()
	:m_SubMenu(SubMenu::NONE), m_ActivityDone(false),
	m_ActivityText(""), m_ActivityDescription(std::make_unique<Text>("", 400.0f, 235.0f, 12.0f, 0.0f)),
	m_RestText(std::make_unique<Text>("", 400.0f, 300.0f, 12.0f, 0.0f)),
	m_Health(std::make_unique<Text>("", 610.0f, 575.0f, 10.0f, 0.0f)),
	m_Day(std::make_unique<Text>("", 400.0f, 575.0f, 10.0f, 0.0f)),
	m_SmithingArrow(std::make_unique<StaticImage>(400.0f, 300.0f, 36, 36, 0.0f, "res/textures/smithArrow.png")),
	m_Fade(std::make_unique<Rectangle>((float)WIDTH / 2.0f, (float)HEIGHT / 2.0f, (float)WIDTH, (float)HEIGHT))
{

	m_Buttons =
	{
		std::make_unique<Button>(180, 50, 200.0f, 425.0f, "res/textures/exploreCavesButton.png", "res/textures/exploreCavesButtonSelected.png"),
		std::make_unique<Button>(180, 50, 400.0f, 425.0f, "res/textures/visitLibraryButton.png", "res/textures/visitLibraryButtonSelected.png"),
		std::make_unique<Button>(180, 50, 600.0f, 425.0f, "res/textures/goFishingButton.png", "res/textures/goFishingButtonSelected.png"),
		std::make_unique<Button>(180, 50, 200.0f, 355.0f, "res/textures/smithButton.png", "res/textures/smithButtonSelected.png"),
		std::make_unique<Button>(180, 50, 400.0f, 355.0f, "res/textures/goTavernButton.png", "res/textures/goTavernButtonSelected.png"),
		std::make_unique<Button>(180, 50, 600.0f, 355.0f, "res/textures/restButton.png", "res/textures/restButtonSelected.png"),
		std::make_unique<Button>(180, 50, 600.0f, 175.0f, "res/textures/nextDayButton.png", "res/textures/nextDayButtonSelected.png"),
		std::make_unique<Button>(180, 50, 400.0f, 190.0f, "res/textures/confirmButton.png", "res/textures/confirmButtonSelected.png"),
		std::make_unique<Button>(180, 50, 690.0f, 125.0f, "res/textures/cancelButton.png", "res/textures/cancelButtonSelected.png"),
		std::make_unique<Button>(50, 43, 570.0f, 578.0f, "res/textures/viewDeckButton.png", "res/textures/viewDeckButtonSelected.png")
	};
	m_Fade->SetColor(0.0f, 0.0f, 0.0f, 0.95f);
	m_Health->SetColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Day->SetColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TowerDefense::Base::Render()
{
	m_Buttons[0]->Render();
	m_Buttons[1]->Render();
	m_Buttons[2]->Render();
	m_Buttons[3]->Render();
	m_Buttons[4]->Render();
	m_Buttons[5]->Render();
	m_Buttons[6]->Render();
	m_Buttons[9]->Render();

	m_Health->Render();
	m_Day->Render();

	switch (m_SubMenu)
	{
	case SubMenu::SMITHING:
		RenderSmithing();
		break;
	case SubMenu::LIBRARY:
		RenderLibrary();
		break;
	case SubMenu::TAVERN:
		RenderTavern();
		break;
	case SubMenu::REST:
		RenderRest();
		break;
	case SubMenu::NONE:
		if (Player::Get().GetDeck()->IsShowing())
		{
			Player::Get().GetDeck()->RenderCards();
			m_Buttons[9]->Render();
		}
		break;
	}

	if (m_ActivityText.size() > 0)
		m_ActivityDescription->Render();
}

void TowerDefense::Base::Update()
{
	switch (m_SubMenu)
	{
	case SubMenu::SMITHING:
		UpdateSmithing();
		break;
	case SubMenu::LIBRARY:
		UpdateLibrary();
		break;
	case SubMenu::TAVERN:
		UpdateTavern();
		break;
	case SubMenu::REST:
		UpdateRest();
		break;
	case SubMenu::NONE:
		if (Player::Get().GetDeck()->IsShowing())
			UpdateDeck();
		else
		{
			UpdateActivities();
			UpdateActivityDescription();
			UpdateViewDeck();
			UpdateNextDay();
		}
		break;
	}
}

void TowerDefense::Base::OnSwitch()
{
	m_ActivityDone = false;

	m_Day = std::make_unique<Text>(std::string("Day: ") + std::to_string(GetDay()), 400.0f, 575.0f, 10.0f, 0.0f);
	m_Day->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_Health = std::make_unique<Text>(std::string("Health: ") + std::to_string(Player::Get().GetHealth()) + "/" + std::to_string(Player::Get().GetMaxHealth()), 700.0f, 575.0f, 10.0f, 0.0f);
	m_Health->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_RestText = std::make_unique<Text>("Rest to restore " + std::to_string(Player::Get().GetMaxHealth() / 10) + " health", 400.0f, 300.0f, 12.0f, 0.0f);
	m_RestText->SetPosition(400.0f, 300.0f, 0);
	m_RestText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::Base::RenderSmithing()
{
	Player::Get().GetDeck()->RenderCards();
	std::shared_ptr<HeroCard> heroCard = std::dynamic_pointer_cast<HeroCard>(m_SelectedCard);
	if (m_SelectedCard && heroCard)
	{
		m_Fade->Render();
		heroCard->GetUpgrades()->Render();
		if (heroCard->GetUpgrades()->GetSelectedCard())
			m_Buttons[7]->Render();
	}
	else if (m_SelectedCard && !m_SelectedCard->IsUpgraded())
	{
		m_Fade->Render();
		m_SelectedCardImage->Render();
		m_SelectedCard->RenderUpgrade(500, 300);
		m_SmithingArrow->Render();
		m_Buttons[7]->Render();
	}
	m_Buttons[8]->Render();
}

void TowerDefense::Base::RenderLibrary()
{
	m_Fade->Render();
	m_CardChoice->Render();
	m_Buttons[8]->Render();
	m_Buttons[9]->Render();
	if (m_CardChoice->GetSelectedCard())
		m_Buttons[7]->Render();
	if (Player::Get().GetDeck()->IsShowing())
	{
		Player::Get().GetDeck()->RenderCards();
		m_Buttons[9]->Render();
	}
}

void TowerDefense::Base::RenderTavern()
{
	m_Fade->Render();
	m_TavernChoice->Render();
	m_Buttons[8]->Render();
	m_Buttons[9]->Render();
	if (m_TavernChoice->GetSelectedCard())
		m_Buttons[7]->Render();
	if (Player::Get().GetDeck()->IsShowing())
	{
		Player::Get().GetDeck()->RenderCards();
		m_Buttons[9]->Render();
	}
}

void TowerDefense::Base::RenderRest()
{
	m_Fade->Render();
	m_Health->Render();
	m_RestText->Render();
	m_Buttons[7]->Render();
	m_Buttons[8]->Render();
}

void TowerDefense::Base::UpdateSmithing()
{
	std::shared_ptr<HeroCard> heroCard = std::dynamic_pointer_cast<HeroCard>(m_SelectedCard);
	if (m_SelectedCard && heroCard)
	{
		heroCard->GetUpgrades()->Update();
		if (heroCard->GetUpgrades()->GetSelectedCard())
		{
			m_Buttons[7]->Update();
			if (m_Buttons[7]->IsClicked())
			{
				m_ActivityDone = true;
				m_SubMenu = SubMenu::NONE;
				Player::Get().GetDeck()->Show(false);
				heroCard->Upgrade();
			}
		}
	}
	else if (m_SelectedCard && !m_SelectedCard->IsUpgraded())
	{
		m_Buttons[7]->Update();
		if (m_Buttons[7]->IsClicked())
		{
			m_ActivityDone = true;
			m_SubMenu = SubMenu::NONE;
			Player::Get().GetDeck()->Show(false);
			m_SelectedCard->Upgrade();
		}
	}
	m_Buttons[8]->Update();
	if (m_Buttons[8]->IsClicked())
	{
		if (m_SelectedCard && !m_SelectedCard->IsUpgraded())
			m_SelectedCard.reset();
		else
		{
			m_SubMenu = SubMenu::NONE;
			Player::Get().GetDeck()->Show(false);
		}
	}
	if (!m_SelectedCard || m_SelectedCard->IsUpgraded())
	{
		Player::Get().GetDeck()->Update();
		FindSelectedCard();
	}
	m_ActivityText = "";
}

void TowerDefense::Base::UpdateLibrary()
{
	Player& player = Player::Get();
	if (player.GetDeck()->IsShowing())
		player.GetDeck()->Update();
	else
	{
		m_CardChoice->Update();
		if (m_CardChoice->GetSelectedCard())
		{
			m_Buttons[7]->Update();
			if (m_Buttons[7]->IsClicked())
			{
				player.GetDeck()->AddCard(m_CardChoice->GetSelectedCard());
				m_SubMenu = SubMenu::NONE;
				m_ActivityDone = true;
				m_CardChoice.reset();
			}
		}
		m_Buttons[8]->Update();
		if (m_Buttons[8]->IsClicked())
			m_SubMenu = SubMenu::NONE;
	}
	m_Buttons[9]->Update();
	if (m_Buttons[9]->IsClicked())
		player.GetDeck()->Show(!player.GetDeck()->IsShowing());
}

void TowerDefense::Base::UpdateTavern()
{
	Player& player = Player::Get();
	if (player.GetDeck()->IsShowing())
		player.GetDeck()->Update();
	else
	{
		m_TavernChoice->Update();
		if (m_TavernChoice->GetSelectedCard())
		{
			m_Buttons[7]->Update();
			if (m_Buttons[7]->IsClicked())
			{
				player.GetDeck()->AddCard(m_TavernChoice->GetSelectedCard());
				m_SubMenu = SubMenu::NONE;
				m_ActivityDone = true;
				m_TavernChoice->RemoveSelectedCard();
			}
		}
		m_Buttons[8]->Update();
		if (m_Buttons[8]->IsClicked())
			m_SubMenu = SubMenu::NONE;
	}
	m_Buttons[9]->Update();
	if (m_Buttons[9]->IsClicked())
		player.GetDeck()->Show(!player.GetDeck()->IsShowing());
}

void TowerDefense::Base::UpdateRest()
{
	m_Buttons[7]->Update();
	if (m_Buttons[7]->IsClicked())
	{
		Player::Get().ChangeHealth(10);
		m_Health = std::make_unique<Text>(std::string("Health: ") + std::to_string(Player::Get().GetHealth()) + "/" + std::to_string(Player::Get().GetMaxHealth()), 700.0f, 575.0f, 10.0f, 0.0f);
		m_Health->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_ActivityDone = true;
		m_SubMenu = SubMenu::NONE;
	}

	m_Buttons[8]->Update();
	if (m_Buttons[8]->IsClicked())
	{
		m_SubMenu = SubMenu::NONE;
	}
}

void TowerDefense::Base::UpdateDeck()
{
	Player& player = Player::Get();
	player.GetDeck()->Update();
	m_Buttons[9]->Update();
	if (m_Buttons[9]->IsClicked())
		player.GetDeck()->Show(!player.GetDeck()->IsShowing());
	m_ActivityText = "";
}

void TowerDefense::Base::UpdateActivities()
{
	if (m_ActivityDone)
		return;

	Player& player = Player::Get();
	m_Buttons[0]->Update();
	if (m_Buttons[0]->IsClicked())
	{
		m_ActivityDone = true;
		m_Buttons[0]->SetSelected(false);
	}
	m_Buttons[1]->Update();
	if (m_Buttons[1]->IsClicked())
	{
		m_SubMenu = SubMenu::LIBRARY;
		if (!m_CardChoice || m_CardChoice->GetGenerationDay() != GetDay())
			m_CardChoice = std::make_unique<CardChoice>(3, GetDay());
		m_Buttons[1]->SetSelected(false);
	}
	m_Buttons[2]->Update();
	if (m_Buttons[2]->IsClicked())
	{
		m_ActivityDone = true;
		m_Buttons[2]->SetSelected(false);
	}
	m_Buttons[3]->Update();
	if (m_Buttons[3]->IsClicked())
	{
		m_SubMenu = SubMenu::SMITHING;
		player.GetDeck()->Show(true);
		m_SelectedCard.reset();
		m_Buttons[3]->SetSelected(false);
	}
	m_Buttons[4]->Update();
	if (m_Buttons[4]->IsClicked())
	{
		m_SubMenu = SubMenu::TAVERN;
		if (!m_TavernChoice || GetDay() - m_TavernChoice->GetGenerationDay() > 3) {
			auto cards = std::make_shared<std::vector<std::shared_ptr<Card>>>();
			for (int i = 0; i < 3; i++)
				cards->push_back(HeroCard::GenerateHero());
			m_TavernChoice = std::make_unique<CardChoice>(cards, GetDay());
		}
		m_Buttons[4]->SetSelected(false);
	}
	m_Buttons[5]->Update();
	if (m_Buttons[5]->IsClicked())
	{
		m_SubMenu = SubMenu::REST;
		m_Buttons[5]->SetSelected(false);
	}

	if (m_Buttons[0]->IsSelected())
		m_ActivityText = "Explore the unknown!";
	else if (m_Buttons[1]->IsSelected())
		m_ActivityText = "Add to your collection.";
	else if (m_Buttons[2]->IsSelected())
		m_ActivityText = "Try to reel somthing in.";
	else if (m_Buttons[3]->IsSelected())
		m_ActivityText = "Upgrade!";
	else if (m_Buttons[4]->IsSelected())
		m_ActivityText = "Meet new people!";
	else if (m_Buttons[5]->IsSelected())
		m_ActivityText = "Lick your wounds.";
	else
		m_ActivityText = "";
}

void TowerDefense::Base::UpdateActivityDescription()
{
	if (m_ActivityText.size() < 1)
		return;

	if (m_ActivityDescription->GetMessage() != m_ActivityText)
	{
		m_ActivityDescription = std::make_unique<Text>(m_ActivityText, 400.0f, 235.0f, 12.0f, 0.0f);
		m_ActivityDescription->SetPosition(400.0f, 235.0f, 0);
		m_ActivityDescription->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void TowerDefense::Base::UpdateViewDeck()
{
	Player::Get().GetDeck()->Update();
	m_Buttons[9]->Update();
	if (m_Buttons[9]->IsClicked())
		Player::Get().GetDeck()->Show(!Player::Get().GetDeck()->IsShowing());
}

void TowerDefense::Base::UpdateNextDay()
{
	m_Buttons[6]->Update();
	if (m_Buttons[6]->IsClicked())
	{
		NextDay();
		SetScene(SceneType::PRECOMBAT);
	}
}

void TowerDefense::Base::FindSelectedCard()
{
	if (!Input::GetMouseClicked())
		return;

	m_SelectedCard = Player::Get().GetDeck()->GetSelectedCard();
	if (m_SelectedCard)
	{
		m_SelectedCardImage = m_SelectedCard->Clone();
		m_SelectedCardImage->SetX(300);
		m_SelectedCardImage->SetY(300);

	}
}