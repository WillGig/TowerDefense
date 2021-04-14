#include "pch.h"
#include "PostCombatScreen.h"
#include "TowerDefense.h"

TowerDefense::PostCombatScreen::PostCombatScreen()
	:m_BackToCamp(std::make_unique<Button>(180, 50, 400.0f, 300.0f, "res/textures/returnToCampButton.png", "res/textures/returnToCampButtonSelected.png"))
{
}

void TowerDefense::PostCombatScreen::Render()
{
	m_BackToCamp->Render();
}

void TowerDefense::PostCombatScreen::Update()
{
	m_BackToCamp->Update();

	if (m_BackToCamp->IsClicked())
		TowerDefense::SetScene(SceneType::BASE);

}

void TowerDefense::PostCombatScreen::OnSwitch()
{
	Renderer::Get().Clear(0.0f, 0.0f, 0.0f, 1.0f);
}