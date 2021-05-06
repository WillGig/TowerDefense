#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "TowerDefense.h"

TowerDefense::Library::Library()
	:BaseScene("visitLibraryButton", "Add to your collection."),
	m_Confirm(std::make_unique<Button>(400.0f, 190.0f, 180, 50, "confirmButton")),
	m_Cancel(std::make_unique<Button>(690.0f, 125.0f, 180, 50, "cancelButton"))
{
}

void TowerDefense::Library::Render()
{
	Player& player = Player::Get();
	player.RenderDeckButton();
	player.RenderArtifactsPile();
	player.RenderStats();
	m_Cancel->Render();
	if (m_CardChoice->GetSelectedCard())
		m_Confirm->Render();
	m_CardChoice->Render();

	if (player.DeckShowing())
	{
		player.RenderDeck();
		if (!player.GetSelectedDeckCard())
			player.RenderDeckButton();
	}
	else if (player.ArtifactsShowing())
	{
		player.RenderArtifacts();
		if (!player.GetSelectedArtifact())
			player.RenderArtifactsPile();
	}
}


void TowerDefense::Library::Update()
{
	Player& player = Player::Get();
	bool showingInfo = m_CardChoice && m_CardChoice->ShowingInfo();

	if (!player.GetSelectedDeckCard() && !showingInfo && !player.ArtifactsShowing())
	{
		player.UpdateDeckButton();
		if (player.DeckButtonClicked())
			player.ToggleDeckShow();
	}

	if (player.DeckShowing())
		player.UpdateDeck();
	else
	{
		player.UpdateArtifactsPile();
		if (!player.ArtifactsShowing())
		{
			if (m_CardChoice->GetSelectedCard() && !showingInfo)
			{
				m_Confirm->Update();
				if (m_Confirm->IsClicked())
				{
					player.AddToDeck(m_CardChoice->GetSelectedCard());
					m_ActivityDone = true;
					m_Exit = true;
					m_CardChoice.reset();
				}
			}
			if (!showingInfo)
			{
				m_Cancel->Update();
				if (m_Cancel->IsClicked())
					m_Exit = true;
			}
			if (m_CardChoice)
				m_CardChoice->Update();
		}
	}
}

void TowerDefense::Library::OnSwitch()
{
	BaseScene::OnSwitch();
	if (!m_CardChoice || m_CardChoice->GetGenerationDay() != GetDay())
		m_CardChoice = std::make_unique<CardChoice>(3, GetDay());
}