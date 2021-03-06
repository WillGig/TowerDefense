#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "TowerDefense.h"
#include "cards/HeroCard.h"
#include "scenes/InGameSettings.h"

TowerDefense::Tavern::Tavern()
	:BaseScene("goTavernButton", "Meet new people!", 5),
	m_Confirm(std::make_unique<Button>(400.0f, 190.0f, 180, 50, "confirmButton")),
	m_Cancel(std::make_unique<Button>(690.0f, 125.0f, 180, 50, "cancelButton"))
{
}

void TowerDefense::Tavern::Render()
{
	Player& player = Player::Get();

	m_Cancel->Render();
	player.RenderStats();
	if (m_TavernChoice->GetSelectedCard())
		m_Confirm->Render();
	m_TavernChoice->Render();
	if (!m_TavernChoice->ShowingInfo())
	{
		InGameSettings::Get().RenderButton();
		player.RenderDeckAndArtifacts();
		if (InGameSettings::Get().IsShowing())
			InGameSettings::Get().Render();
	}
}

void TowerDefense::Tavern::Update()
{
	Player& player = Player::Get();
	bool showingInfo = m_TavernChoice && m_TavernChoice->ShowingInfo();

	if (!showingInfo)
	{
		if (InGameSettings::Get().IsShowing())
		{
			InGameSettings::Get().Update();
			return;
		}

		Player& player = Player::Get();
		player.UpdateDeckAndArtifacts();

		if (player.DeckShowing() || player.ArtifactsShowing())
			return;

		InGameSettings::Get().UpdateButton();
	}

	if (m_TavernChoice->GetSelectedCard() && !showingInfo)
	{
		m_Confirm->Update();
		if (m_Confirm->IsClicked())
		{
			player.AddToDeck(m_TavernChoice->GetSelectedCard());
			m_ActivityReady = m_ActivityCoolDown;
			m_Exit = true;
		}
	}
	if (!showingInfo)
	{
		m_Cancel->Update();
		if (m_Cancel->IsClicked())
		{
			m_Exit = true;
			m_ActivityReady = m_ActivityCoolDown;
		}
			
	}
	if (m_TavernChoice)
		m_TavernChoice->Update();
}

void TowerDefense::Tavern::OnSwitch()
{
	BaseScene::OnSwitch();
	auto cards = std::make_shared<std::vector<std::shared_ptr<Card>>>();
	for (int i = 0; i < 3; i++)
		cards->push_back(HeroCard::GenerateHero());
	m_TavernChoice = std::make_unique<CardChoice>(cards, GetDay());
}