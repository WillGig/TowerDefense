#include "pch.h"
#include "Base.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "cards/HeroCard.h"

TowerDefense::Base::Base()
	:m_CurrentMenu(-1), m_ActivityDone(false),
	m_NextDay(std::make_unique<Button>(600.0f, 175.0f, 180, 50, "nextDayButton")),
	m_BaseScenes(std::make_unique<std::vector<std::shared_ptr<BaseScene>>>())
{
	AddBaseScene(std::make_shared<Rest>());
	AddBaseScene(std::make_shared<Caves>());
	AddBaseScene(std::make_shared<Library>());
	AddBaseScene(std::make_shared<Smithing>());
	AddBaseScene(std::make_shared<Tavern>());
	AddBaseScene(std::make_shared<Chapel>());
}

void TowerDefense::Base::Render()
{
	Player& player = Player::Get();

	if (m_CurrentMenu == -1)
	{
		for (unsigned int i = 0; i < m_BaseScenes->size(); i++)
		{
			m_BaseScenes->at(i)->RenderButton();
			if (m_BaseScenes->at(i)->ButtonSelected())
				m_BaseScenes->at(i)->RenderText();
		}
		m_NextDay->Render();
		player.RenderDeckButton();
		player.RenderArtifactsPile();
		player.RenderHealth();
		player.RenderGold();
		player.RenderDay();

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
	else
	{
		m_BaseScenes->at(m_CurrentMenu)->Render();
	}
}

void TowerDefense::Base::Update()
{
	if (m_CurrentMenu == -1)
	{
		Player& player = Player::Get();
		if (player.DeckShowing())
			UpdateDeck();
		else if (player.ArtifactsShowing())
			player.UpdateArtifactsPile();
		else
		{
			UpdateActivities();
			UpdateViewDeck();
			UpdateNextDay();
		}
	}
	else
	{
		m_BaseScenes->at(m_CurrentMenu)->Update();
		if (m_BaseScenes->at(m_CurrentMenu)->Exit())
		{
			m_ActivityDone = m_BaseScenes->at(m_CurrentMenu)->ActivityDone();
			m_CurrentMenu = -1;
		}
	}
}

void TowerDefense::Base::OnSwitch()
{
	m_ActivityDone = false;
	Player::Get().SetTextColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::Base::UpdateDeck()
{
	Player& player = Player::Get();
	if (!player.GetSelectedDeckCard())
	{
		player.UpdateDeckButton();
		if (player.DeckButtonClicked())
			player.ToggleDeckShow();
	}
	player.UpdateDeck();
}

void TowerDefense::Base::UpdateActivities()
{
	if (m_ActivityDone)
		return;

	for (unsigned int i = 0; i < m_BaseScenes->size(); i++)
	{
		m_BaseScenes->at(i)->UpdateButton();
		if (m_BaseScenes->at(i)->ButtonClicked())
		{
			m_CurrentMenu = i;
			m_BaseScenes->at(i)->OnSwitch();
			return;
		}
	}
}

void TowerDefense::Base::UpdateViewDeck()
{
	Player& player = Player::Get();
	player.UpdateDeckButton();
	if (player.DeckButtonClicked())
	{
		player.ToggleDeckShow();
	}
	player.UpdateDeck();

	player.UpdateArtifactsPile();
}

void TowerDefense::Base::UpdateNextDay()
{
	m_NextDay->Update();
	if (m_NextDay->IsClicked())
	{
		NextDay();
		SetScene(SceneType::PRECOMBAT);
	}
}

void TowerDefense::Base::AddBaseScene(std::shared_ptr<BaseScene> scene)
{
	int position = m_BaseScenes->size();
	scene->SetButtonPosition((position % 3) *200.0f + 200.0f, 425 - (position/3) * 70.0f);
	m_BaseScenes->push_back(scene);
}