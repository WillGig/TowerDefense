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

	if (!player.GetSelectedDeckCard())
		player.RenderDeckButton();
}

void TowerDefense::Caves::Update()
{
	Player& player = Player::Get();

	if (!player.GetSelectedDeckCard())
	{
		player.UpdateDeckButton();
		if (player.DeckButtonClicked())
			player.ToggleDeckShow();
	}

	if (player.DeckShowing())
		player.UpdateDeck();
	else
		m_CaveScene->Update();

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