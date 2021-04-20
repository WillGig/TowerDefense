#include "pch.h"
#include "PreCombatScreen.h"
#include "TowerDefense.h"

TowerDefense::PreCombatScreen::PreCombatScreen()
	:m_BeginCombat(std::make_unique<Button>(180, 50, 400.0f, 300.0f, "beginCombatButton", "beginCombatButtonSelected")
)
{
}

void TowerDefense::PreCombatScreen::Render()
{
	m_BeginCombat->Render();
}

void TowerDefense::PreCombatScreen::Update()
{
	m_BeginCombat->Update();

	if (m_BeginCombat->IsClicked())
		TowerDefense::SetScene(SceneType::COMBAT);
}

void TowerDefense::PreCombatScreen::OnSwitch()
{

}