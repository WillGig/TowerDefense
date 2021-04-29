#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"

TowerDefense::Caves::Caves()
	:BaseScene("exploreCavesButton", "Explore the unknown!")
{
}

void TowerDefense::Caves::Render()
{
	Player& player = Player::Get();

	m_Fade->Render();
	m_CaveScene->Render();

	player.RenderHealth();
	player.RenderDay();

	if (player.DeckShowing())
		player.RenderDeck();
	else if (player.ArtifactsShowing())
		player.RenderArtifacts();

	if (!player.GetSelectedDeckCard() && !player.ArtifactsShowing())
		player.RenderDeckButton();
	if(!player.GetSelectedArtifact() && !player.DeckShowing())
		player.RenderArtifactsPile();
}

void TowerDefense::Caves::Update()
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
			m_CaveScene->Update();
	}

	if (m_CaveScene->Exit())
	{
		m_ActivityDone = true;
		m_Exit = true;
		//Update player health?
	}
}

void TowerDefense::Caves::OnSwitch()
{
	BaseScene::OnSwitch();
	m_CaveScene = CaveScene::GetRandomCaveEvent();
}