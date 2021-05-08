#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "TowerDefense.h"
#include "cards/HeroCard.h"

TowerDefense::Tavern::Tavern()
	:BaseScene("goTavernButton", "Meet new people!"),
	m_Confirm(std::make_unique<Button>(400.0f, 190.0f, 180, 50, "confirmButton")),
	m_Cancel(std::make_unique<Button>(690.0f, 125.0f, 180, 50, "cancelButton"))
{
}

void TowerDefense::Tavern::Render()
{
	Player& player = Player::Get();

	m_Cancel->Render();
	player.RenderStats();
	player.RenderDeckAndArtifacts();
	if (m_TavernChoice->GetSelectedCard())
		m_Confirm->Render();
	m_TavernChoice->Render();
}

void TowerDefense::Tavern::Update()
{
	Player& player = Player::Get();
	bool showingInfo = m_TavernChoice && m_TavernChoice->ShowingInfo();

	if (!showingInfo)
		player.UpdateDeckAndArtifacts();

	if (!player.DeckShowing() && !player.ArtifactsShowing())
	{
		if (m_TavernChoice->GetSelectedCard() && !showingInfo)
		{
			m_Confirm->Update();
			if (m_Confirm->IsClicked())
			{
				player.AddToDeck(m_TavernChoice->GetSelectedCard());
				m_ActivityDone = true;
				m_Exit = true;
				m_TavernChoice->RemoveSelectedCard();
			}
		}
		if (!showingInfo)
		{
			m_Cancel->Update();
			if (m_Cancel->IsClicked())
				m_Exit = true;
		}
		if (m_TavernChoice)
			m_TavernChoice->Update();
	}
}

void TowerDefense::Tavern::OnSwitch()
{
	BaseScene::OnSwitch();
	if (!m_TavernChoice || GetDay() - m_TavernChoice->GetGenerationDay() > 3) {
		auto cards = std::make_shared<std::vector<std::shared_ptr<Card>>>();
		for (int i = 0; i < 3; i++)
			cards->push_back(HeroCard::GenerateHero());
		m_TavernChoice = std::make_unique<CardChoice>(cards, GetDay());
	}
}