#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"

TowerDefense::Caves::Caves()
	:BaseScene("exploreCavesButton", "Explore the unknown or Dig for Gold!"), 
	m_GoldMined(0), m_CurrentActivity(Activity::MENU),
	m_Explore(std::make_unique<Button>(300.0f, 300.0f, 180, 50, "exploreButton")),
	m_Mine(std::make_unique<Button>(500.0f, 300.0f, 180, 50, "mineButton")),
	m_BackToCamp(std::make_unique<Button>(400.0f, 200.0f, 180, 50, "returnToCampButton"))
{
}

void TowerDefense::Caves::Render()
{
	Player& player = Player::Get();

	if (m_CurrentActivity == Activity::MENU)
	{
		m_Explore->Render();
		m_Mine->Render();
		m_BackToCamp->Render();
	}
	else if (m_CurrentActivity == Activity::EXPLORE)
	{
		m_CaveScene->Render();
	}
	else if (m_CurrentActivity == Activity::MINE)
	{
		m_MiningText->Render();
		m_BackToCamp->Render();
	}

	player.RenderStats();
	player.RenderDeckAndArtifacts();
}

void TowerDefense::Caves::Update()
{
	Player& player = Player::Get();
	player.UpdateDeckAndArtifacts();
	
	if (m_CurrentActivity == Activity::MENU)
	{
		m_Explore->Update();
		if (m_Explore->IsClicked())
			m_CurrentActivity = Activity::EXPLORE;

		m_Mine->Update();
		if (m_Mine->IsClicked())
		{
			m_CurrentActivity = Activity::MINE;
			m_GoldMined = 25 + (int)(Random::GetFloat() * 50);
			m_MiningText = std::make_unique<Text>("You manage to mine " + std::to_string(m_GoldMined) + " Gold", 400.0f, 300.0f, 12.0f, 0.0f);
			m_MiningText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		m_BackToCamp->Update();
		if (m_BackToCamp->IsClicked())
			m_Exit = true;
	}
	else if (m_CurrentActivity == Activity::EXPLORE)
	{
		if (!player.DeckShowing() && !player.ArtifactsShowing())
			m_CaveScene->Update();
		if (m_CaveScene->Exit())
		{
			m_Exit = true;
			m_ActivityDone = true;
		}
	}
	else if (m_CurrentActivity == Activity::MINE)
	{
		m_BackToCamp->Update();
		if (m_BackToCamp->IsClicked())
		{
			Player::Get().ChangeResource(m_GoldMined, Resource::GOLD);
			m_Exit = true;
			m_ActivityDone = true;
		}
	}
}

void TowerDefense::Caves::OnSwitch()
{
	BaseScene::OnSwitch();
	m_CaveScene = CaveScene::GetRandomCaveEvent();
	m_CurrentActivity = Activity::MENU;
}