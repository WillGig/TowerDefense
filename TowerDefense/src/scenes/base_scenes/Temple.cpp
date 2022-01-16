#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "scenes/InGameSettings.h"

TowerDefense::Temple::Temple()
	:BaseScene("meditateButton", "Strengthen your resolve", 0),
	m_BackToCamp(std::make_unique<Button>(690.0f, 60.0f, 180, 50, "returnToCampButton"))
{}

void TowerDefense::Temple::Render()
{
	m_BackToCamp->Render();

	Player& player = Player::Get();
	InGameSettings::Get().RenderButton();
	player.RenderStats();
	player.RenderDeckAndArtifacts();
	if (InGameSettings::Get().IsShowing())
		InGameSettings::Get().Render();
}

void TowerDefense::Temple::Update()
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

void TowerDefense::Temple::OnSwitch()
{
	BaseScene::OnSwitch();
}