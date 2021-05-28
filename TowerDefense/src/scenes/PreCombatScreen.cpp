#include "pch.h"
#include "PreCombatScreen.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "Combat.h"

TowerDefense::PreCombatScreen::PreCombatScreen()
	:m_BeginCombat(std::make_unique<Button>(400.0f, 100.0f, 180, 50, "beginCombatButton")),
	m_IncomingText(std::make_unique<Text>("Enemies Incoming!", 400.0f, 450.0f, 36.0f, 0.0f))
{
	m_IncomingText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::PreCombatScreen::Render()
{
	m_IncomingText->Render();
	m_BeginCombat->Render();
	
	Player& player = Player::Get();
	player.RenderStats();

	for (unsigned int i = 0; i < m_Enemies.size(); i++)
		m_Enemies[i]->Render();

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
	m_Enemies = std::vector<std::unique_ptr<EnemyIcon>>();

	auto fight = Combat::GetNextFight();

	for (int i = 0; i < fight->NumberOfWaves(); i++)
	{
		auto wave = fight->GetWave(i);
		for (int j = 0; j < wave->NumberOfEnemies(); j++)
		{
			auto enemy = wave->Getenemy(j);
			if (!ContainsEnemy(enemy->GetName()))
				m_Enemies.push_back(std::make_unique<EnemyIcon>(enemy));
		}
	}

	for (unsigned int i = 0; i < m_Enemies.size(); i++)
		m_Enemies[i]->SetPosition(400.0f + (i - (m_Enemies.size() - 1) / 2.0f) * 100.0f, 300.0f);
}

bool TowerDefense::PreCombatScreen::ContainsEnemy(const std::string& name) const
{
	for (unsigned int i = 0; i < m_Enemies.size(); i++)
	{
		if (m_Enemies[i]->GetName() == name)
			return true;
	}
	return false;
};