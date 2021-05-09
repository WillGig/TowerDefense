#include "pch.h"
#include "PreCombatScreen.h"
#include "TowerDefense.h"
#include "core/Player.h"

TowerDefense::PreCombatScreen::PreCombatScreen()
	:m_BeginCombat(std::make_unique<Button>(400.0f, 300.0f, 180, 50, "beginCombatButton")
)
{
}

void TowerDefense::PreCombatScreen::Render()
{
	m_BeginCombat->Render();
	
	Player& player = Player::Get();
	player.RenderStats();
	player.RenderDeckAndArtifacts();
}

void TowerDefense::PreCombatScreen::Update()
{
	Player& player = Player::Get();
	player.UpdateDeckAndArtifacts();

	if (!player.DeckShowing() && !player.ArtifactsShowing())
	{
		m_BeginCombat->Update();

		if (m_BeginCombat->IsClicked())
			TowerDefense::SetScene(SceneType::COMBAT);
	}
}

void TowerDefense::PreCombatScreen::OnSwitch()
{

}