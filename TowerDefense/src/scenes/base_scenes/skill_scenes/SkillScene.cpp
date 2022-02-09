#include "pch.h"
#include "SkillScene.h"
#include "core/Player.h"
#include "scenes/InGameSettings.h"

TowerDefense::SkillScene::SkillScene(const std::string& button, const std::string& description, int coolDown)
	:BaseScene(button, description, coolDown), m_BackToCamp(std::make_unique<Button>(690.0f, 60.0f, 180, 50, "returnToCampButton"))
{}

void TowerDefense::SkillScene::Render()
{
	m_BackToCamp->Render();

	m_Tree->Render();
	if (m_Tree->GetSelectedSkill())
		m_Tree->GetSelectedSkill()->RenderInfo();

	Player& player = Player::Get();
	InGameSettings::Get().RenderButton();
	player.RenderStats();
	player.RenderDeckAndArtifacts();
	if (InGameSettings::Get().IsShowing())
		InGameSettings::Get().Render();
}

void TowerDefense::SkillScene::Update()
{
	if (InGameSettings::Get().IsShowing())
	{
		InGameSettings::Get().Update();
		return;
	}

	Player& player = Player::Get();
	player.UpdateDeckAndArtifacts();

	if (!player.DeckShowing() && !player.ArtifactsShowing())
	{
		InGameSettings::Get().UpdateButton();

		int oldApplied = m_Tree->GetNumApplied();
		m_Tree->Update();
		if (oldApplied < m_Tree->GetNumApplied())
		{
			m_ActivityReady = m_ActivityCoolDown;
			m_Exit = true;
		}

		m_BackToCamp->Update();
		if (m_BackToCamp->IsClicked())
			m_Exit = true;
	}
}