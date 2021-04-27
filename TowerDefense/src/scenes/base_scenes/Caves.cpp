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

	auto deck = player.GetDeck();
	if (deck->IsShowing())
		deck->RenderCards();

	if (!deck->GetSelectedCard())
		player.RenderDeckButton();
}

void TowerDefense::Caves::Update()
{
	Player& player = Player::Get();
	auto deck = player.GetDeck();

	if (!deck->GetSelectedCard())
	{
		player.UpdateDeckButton();
		if (player.DeckButtonClicked())
			deck->Show(!deck->IsShowing());
	}

	if (deck->IsShowing())
		deck->Update();
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