#include "pch.h"
#include "PostCombatScreen.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "scenes/Combat.h"

TowerDefense::PostCombatScreen::PostCombatScreen()
	:m_FocusedReward(-1), m_BackToCamp(std::make_unique<Button>(400.0f, 100.0f, 180, 50, "returnToCampButton")),
	m_Rewards(std::make_unique<std::vector<std::shared_ptr<CombatReward>>>())
{
}

void TowerDefense::PostCombatScreen::Render()
{
	Player& player = Player::Get();
	player.RenderDeckButton();
	player.RenderArtifactsPile();
	player.RenderStats();

	m_DefeatedStats->Render();
	m_EscapedStats->Render();
	m_DamageDealt->Render();

	for (unsigned int i = 0; i < m_Rewards->size(); i++)
	{
		if(i != m_FocusedReward)
			m_Rewards->at(i)->Render();
	}
	m_BackToCamp->Render();

	if (m_FocusedReward != -1)
		m_Rewards->at(m_FocusedReward)->Render();

	if (player.DeckShowing())
	{
		player.RenderDeck();
		if (!player.GetSelectedDeckCard())
			player.RenderDeckButton();
	}
	else if (player.ArtifactsShowing())
	{
		player.RenderArtifacts();
		if (!player.GetSelectedArtifact())
			player.RenderArtifactsPile();
	}
}

void TowerDefense::PostCombatScreen::Update()
{
	m_FocusedReward = -1;
	for (unsigned int i = 0; i < m_Rewards->size(); i++)
	{
		if (m_Rewards->at(i)->RequiresFocus())
		{
			m_FocusedReward = i;
			break;
		}
	}

	bool showingRewardInfo = m_FocusedReward != -1 && m_Rewards->at(m_FocusedReward)->ShowingInfo();

	Player& player = Player::Get();
	if (!player.ArtifactsShowing() && !showingRewardInfo)
	{
		player.UpdateDeckButton();
		if (player.DeckButtonClicked())
			player.ToggleDeckShow();
	}

	if (player.DeckShowing())
		player.UpdateDeck();
	else
	{
		if(!showingRewardInfo)
			player.UpdateArtifactsPile();
		if (!player.ArtifactsShowing())
		{
			if (m_FocusedReward == -1)
			{
				int takenReward = -1;
				for (unsigned int i = 0; i < m_Rewards->size(); i++)
				{
					m_Rewards->at(i)->Update();
					if (m_Rewards->at(i)->RewardTaken())
						takenReward = i;
				}

				if (takenReward != -1)
					RemoveReward(takenReward);

				m_BackToCamp->Update();
				if (m_BackToCamp->IsClicked())
					TowerDefense::SetScene(SceneType::BASE);
			}
			else
				m_Rewards->at(m_FocusedReward)->Update();
		}
	}
}

void TowerDefense::PostCombatScreen::OnSwitch()
{
	Renderer::Get().Clear(0.0f, 0.0f, 0.0f, 1.0f);
	Player::Get().SetTextColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Rewards->clear();

	auto fight = Combat::GetCurrentFight();

	auto defeatedEnemies = fight->m_DefeatedEnemies;
	int enemyGold = 0;
	int defeatedHeight = 3;
	std::string defEnemies = "Enemies Defeated:\n\n";
	for (auto i = defeatedEnemies.begin(); i != defeatedEnemies.end(); i++)
	{
		if (i->first == "Rat")
			enemyGold += 5 * i->second;
		else if (i->first == "Giant Rat")
			enemyGold += 10 * i->second;
		else if (i->first == "Boss Rat")
			enemyGold += 100 * i->second;
		else if (i->first == "Goblin")
			enemyGold += 10 * i->second;
		else if (i->first == "Orc")
			enemyGold += 20 * i->second;

		defEnemies += i->first;
		
		for (int j = 0; j < 21 - (int)i->first.size(); j++)
			defEnemies += " ";

		defEnemies += std::to_string(i->second) + "\n";
		defeatedHeight++;
	}

	auto escapedEnemies = fight->m_EscapedEnemies;
	std::string escEnemies = "Enemies Escaped:\n\n";
	int escapedHeight = 3;
	for (auto i = escapedEnemies.begin(); i != escapedEnemies.end(); i++)
	{
		escEnemies += i->first;

		for (int j = 0; j < 21 - (int)i->first.size(); j++)
			escEnemies += " ";

		escEnemies += std::to_string(i->second) + "\n";
		escapedHeight++;
	}

	std::string towerDamage = std::to_string(fight->GetTowerDamage());
	std::string skillDamage = std::to_string(fight->GetSkillDamage());
	std::string artifactDamage = std::to_string(fight->GetArtifactDamage());

	std::string damageDealt = "Damage Dealt:\n\nTowers:";
	
	for (int i = 0; i < 11 - (int)towerDamage.size(); i++)
		damageDealt += " ";
	damageDealt += towerDamage + "\nSkills:";

	for (int i = 0; i < 14 - (int)skillDamage.size(); i++)
		damageDealt += " ";
	damageDealt += skillDamage + "\nArtifacts:";

	for (int i = 0; i < 9 - (int)artifactDamage.size(); i++)
		damageDealt += " ";
	damageDealt += artifactDamage;

	m_DamageDealt = std::make_unique<Text>(damageDealt, 655.0f, 430.0f, 12.0f, 0.0f);
	m_DamageDealt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_DefeatedStats = std::make_unique<Text>(defEnemies, 155.0f, 480.0f - (defeatedHeight * 10.0f), 12.0f, 0.0f);
	m_DefeatedStats->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_EscapedStats = std::make_unique<Text>(escEnemies, 155.0f, 300.0f - (escapedHeight * 10.0f), 12.0f, 0.0f);
	m_EscapedStats->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Combat Gold
	AddReward(std::make_shared<GoldReward>((int)(Random::GetFloat() * 200.0f)));

	//Enemy Reward Gold
	if(enemyGold > 0)
		AddReward(std::make_shared<GoldReward>(enemyGold));

	//Combat Card
	AddReward(std::make_shared<CardReward>(3));
}

void TowerDefense::PostCombatScreen::AddReward(std::shared_ptr<CombatReward> reward)
{
	reward->SetPosition(400.0f, 450.0f - m_Rewards->size() * 50);
	m_Rewards->push_back(reward);
}

void TowerDefense::PostCombatScreen::RemoveReward(int reward)
{
	m_Rewards->erase(m_Rewards->begin() + reward);

	//Shift rewards that come afterwards up
	for (unsigned int i = reward; i < m_Rewards->size(); i++)
		m_Rewards->at(i)->SetPosition(400.0f, 450.0f - i * 50);
}