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

	m_CaveScene->Render();

	player.RenderStats();
	player.RenderDeckAndArtifacts();
}

void TowerDefense::Caves::Update()
{
	Player& player = Player::Get();
	player.UpdateDeckAndArtifacts();
	
	if (!player.DeckShowing() && !player.ArtifactsShowing())
		m_CaveScene->Update();

	if (m_CaveScene->Exit())
	{
		m_ActivityDone = true;
		m_Exit = true;
	}
}

void TowerDefense::Caves::OnSwitch()
{
	BaseScene::OnSwitch();
	m_CaveScene = CaveScene::GetRandomCaveEvent();
}