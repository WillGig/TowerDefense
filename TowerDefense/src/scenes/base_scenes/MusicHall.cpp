#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "scenes/InGameSettings.h"

TowerDefense::MusicHall::MusicHall()
	:BaseScene("composeButton", "Express yourself", 0),
	m_BackToCamp(std::make_unique<Button>(690.0f, 60.0f, 180, 50, "returnToCampButton"))
{}

void TowerDefense::MusicHall::Render()
{
	m_BackToCamp->Render();

	Player& player = Player::Get();
	InGameSettings::Get().RenderButton();
	player.RenderStats();
	player.RenderDeckAndArtifacts();
	if (InGameSettings::Get().IsShowing())
		InGameSettings::Get().Render();
}

void TowerDefense::MusicHall::Update()
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

	m_BackToCamp->Update();
	if (m_BackToCamp->IsClicked())
		m_Exit = true;
}

void TowerDefense::MusicHall::OnSwitch()
{
	BaseScene::OnSwitch();
}