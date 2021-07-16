#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"

TowerDefense::AlchemyLab::AlchemyLab()
	:BaseScene("experimentButton", "Make something explode", 0),
	m_BackToCamp(std::make_unique<Button>(690.0f, 60.0f, 180, 50, "returnToCampButton"))
{}

void TowerDefense::AlchemyLab::Render()
{
	Player& player = Player::Get();
	player.RenderStats();

	m_BackToCamp->Render();

	player.RenderDeckAndArtifacts();
}

void TowerDefense::AlchemyLab::Update()
{
	Player& player = Player::Get();
	player.UpdateDeckAndArtifacts();

	if (!player.DeckShowing() && !player.ArtifactsShowing())
	{
		m_BackToCamp->Update();
		if (m_BackToCamp->IsClicked())
			m_Exit = true;
	}
}

void TowerDefense::AlchemyLab::OnSwitch()
{
	BaseScene::OnSwitch();
}