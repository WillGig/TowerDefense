#include "pch.h"
#include "PreCombatScreen.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "Combat.h"
#include "cards/SideboardSlot.h"

TowerDefense::PreCombatScreen::PreCombatScreen()
	:m_CurrentCardSlot(-1), m_BeginCombat(std::make_unique<Button>(400.0f, 100.0f, 180, 50, "beginCombatButton")),
	m_IncomingText(std::make_unique<Text>("Enemies Incoming!", 400.0f, 450.0f, 36.0f, 0.0f))
{
	m_IncomingText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::PreCombatScreen::Render()
{
	Player& player = Player::Get();
	auto sideboardSlots = player.GetSideBoardSlots();

	if (m_CurrentCardSlot != -1)
	{
		sideboardSlots->at(m_CurrentCardSlot)->Render();
	}
	else
	{
		m_IncomingText->Render();
		m_BeginCombat->Render();

		player.RenderStats();
		InGameSettings::Get().RenderButton();

		for (unsigned int i = 0; i < m_Enemies.size(); i++)
			m_Enemies[i]->Render();


		for (unsigned int i = 0; i < sideboardSlots->size(); i++)
			sideboardSlots->at(i)->Render();

		player.RenderDeckAndArtifacts();

		if (InGameSettings::Get().IsShowing())
			InGameSettings::Get().Render();
	}
}

void TowerDefense::PreCombatScreen::Update()
{
	if (InGameSettings::Get().IsShowing())
	{
		InGameSettings::Get().Update();
		return;
	}

	Player& player = Player::Get();
	auto sideboardSlots = player.GetSideBoardSlots();

	if (m_CurrentCardSlot != -1)
	{
		sideboardSlots->at(m_CurrentCardSlot)->Update();
		if (!sideboardSlots->at(m_CurrentCardSlot)->SelectingCard())
			m_CurrentCardSlot = -1;
	}
	else
	{
		player.UpdateDeckAndArtifacts();

		if (!player.DeckShowing() && !player.ArtifactsShowing())
		{

			InGameSettings::Get().UpdateButton();

			for (unsigned int i = 0; i < sideboardSlots->size(); i++)
			{
				sideboardSlots->at(i)->Update();
				if (sideboardSlots->at(i)->SelectingCard())
					m_CurrentCardSlot = i;
			}

			m_BeginCombat->Update();
			if (m_BeginCombat->IsClicked())
				TowerDefense::SetScene(SceneType::COMBAT);
		}
	}
}

void TowerDefense::PreCombatScreen::OnSwitch()
{
	InGameSettings::Get().Show(false);

	m_Enemies = std::vector<std::unique_ptr<EnemyIcon>>();

	auto fight = Combat::GetNextFight();

	for (int i = 0; i < fight->GetNumberOfWaves(); i++)
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
		m_Enemies[i]->SetPosition(400.0f + (i - (m_Enemies.size() - 1) / 2.0f) * 100.0f, 350.0f);

	auto sideboardSlots = Player::Get().GetSideBoardSlots();
	for (unsigned int i = 0; i < sideboardSlots->size(); i++)
		sideboardSlots->at(i)->Clear();
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