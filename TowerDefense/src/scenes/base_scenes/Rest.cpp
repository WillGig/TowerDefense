#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"

TowerDefense::Rest::Rest()
	:BaseScene("restButton", "Lick your wounds."),
	m_Confirm(std::make_unique<Button>(400.0f, 190.0f, 180, 50, "confirmButton")),
	m_Cancel(std::make_unique<Button>(690.0f, 125.0f, 180, 50, "cancelButton")),
	m_RestText(std::make_unique<Text>("", 400.0f, 300.0f, 12.0f, 0.0f))
{
}

void TowerDefense::Rest::Render()
{
	Player& player = Player::Get();
	player.RenderDeckButton();
	player.RenderArtifactsPile();
	player.RenderStats();
	m_RestText->Render();
	m_Confirm->Render();
	m_Cancel->Render();

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

void TowerDefense::Rest::Update()
{
	Player& player = Player::Get();
	if (!player.ArtifactsShowing())
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
			m_Confirm->Update();
			if (m_Confirm->IsClicked())
			{
				player.ChangeHealth(player.GetMaxHealth() / 5);
				m_ActivityDone = true;
				m_Exit = true;
			}

			m_Cancel->Update();
			if (m_Cancel->IsClicked())
				m_Exit = true;
		}
	}
}

void TowerDefense::Rest::OnSwitch()
{
	BaseScene::OnSwitch();
	m_RestText = std::make_unique<Text>("Rest to restore " + std::to_string(Player::Get().GetMaxHealth() / 5) + " health", 400.0f, 300.0f, 12.0f, 0.0f);
	m_RestText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}