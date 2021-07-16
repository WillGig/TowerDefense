#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"

TowerDefense::WizardTower::WizardTower()
	:BaseScene("studyButton", "Conduct your research", 0),
	m_BackToCamp(std::make_unique<Button>(690.0f, 60.0f, 180, 50, "returnToCampButton"))
{}

void TowerDefense::WizardTower::Render()
{
	Player& player = Player::Get();
	player.RenderStats();

	m_BackToCamp->Render();

	player.RenderDeckAndArtifacts();
}

void TowerDefense::WizardTower::Update()
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

void TowerDefense::WizardTower::OnSwitch()
{
	BaseScene::OnSwitch();
}