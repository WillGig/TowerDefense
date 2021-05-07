#include "pch.h"
#include "PostCombatScreen.h"
#include "TowerDefense.h"
#include "core/Player.h"

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
	AddReward(std::make_shared<GoldReward>((int)(Random::GetFloat() * 200.0f)));
	AddReward(std::make_shared<GoldReward>((int)(Random::GetFloat() * 200.0f)));
	AddReward(std::make_shared<GoldReward>((int)(Random::GetFloat() * 200.0f)));
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