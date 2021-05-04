#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"

TowerDefense::Build::Build()
	:BaseScene("buildButton", "Create something new."),
	m_Confirm(std::make_unique<Button>(400.0f, 190.0f, 180, 50, "confirmButton")),
	m_Cancel(std::make_unique<Button>(690.0f, 125.0f, 180, 50, "cancelButton"))
{
}

void TowerDefense::Build::Render()
{
	Player& player = Player::Get();
	player.RenderDeckButton();
	player.RenderArtifactsPile();
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

void TowerDefense::Build::Update()
{
	Player& player = Player::Get();

	if (!player.GetSelectedDeckCard() && !player.ArtifactsShowing())
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
			//TODO: base choices
			m_Cancel->Update();
			if (m_Cancel->IsClicked())
				m_Exit = true;
		}
	}
}

void TowerDefense::Build::OnSwitch()
{
	BaseScene::OnSwitch();
}