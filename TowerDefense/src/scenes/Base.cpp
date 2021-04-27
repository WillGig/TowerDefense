#include "pch.h"
#include "Base.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "cards/HeroCard.h"

TowerDefense::Base::Base()
	:m_CurrentMenu(-1), m_ActivityDone(false),
	m_NextDay(std::make_unique<Button>(600.0f, 175.0f, 180, 50, "nextDayButton")),
	m_BaseScenes(std::make_unique<std::vector<std::shared_ptr<BaseScene>>>()),
	m_ActivityText(""), m_ActivityDescription(std::make_unique<Text>("", 400.0f, 235.0f, 12.0f, 0.0f))
{

	AddBaseScene(std::make_shared<Rest>(600.0f, 355.0f));
	AddBaseScene(std::make_shared<Caves>(200.0f, 425.0f));
	AddBaseScene(std::make_shared<Library>(400.0f, 425.0f));
	AddBaseScene(std::make_shared<Smithing>(200.0f, 355.0f));
	AddBaseScene(std::make_shared<Tavern>(400.0f, 355.0f));
}

void TowerDefense::Base::Render()
{
	Player& player = Player::Get();

	if (m_CurrentMenu == -1)
	{
		for (unsigned int i = 0; i < m_BaseScenes->size(); i++)
		{
			m_BaseScenes->at(i)->RenderButton();
		}
		m_NextDay->Render();
		player.RenderDeckButton();
		player.RenderHealth();
		player.RenderDay();

		if (player.GetDeck()->IsShowing())
		{
			player.GetDeck()->RenderCards();
			if (!player.GetDeck()->GetSelectedCard())
				player.RenderDeckButton();
		}
	}
	else
	{
		m_BaseScenes->at(m_CurrentMenu)->Render();
	}

	if (m_ActivityText.size() > 0)
		m_ActivityDescription->Render();
}

void TowerDefense::Base::Update()
{
	if (m_CurrentMenu == -1)
	{
		if (Player::Get().GetDeck()->IsShowing())
			UpdateDeck();
		else
		{
			UpdateActivities();
			UpdateActivityDescription();
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
	auto deck = player.GetDeck();
	if (!deck->GetSelectedCard())
	{
		player.UpdateDeckButton();
		if (player.DeckButtonClicked())
			deck->Show(!deck->IsShowing());
	}
	deck->Update();
	m_ActivityText = "";
}

void TowerDefense::Base::UpdateActivities()
{
	if (m_ActivityDone)
		return;

	m_ActivityText = "";
	for (unsigned int i = 0; i < m_BaseScenes->size(); i++)
	{
		m_BaseScenes->at(i)->UpdateButton();
		if (m_BaseScenes->at(i)->ButtonClicked())
		{
			m_CurrentMenu = i;
			m_BaseScenes->at(i)->OnSwitch();
			m_ActivityText = "";
			return;
		}

		if (m_BaseScenes->at(i)->ButtonSelected())
			m_ActivityText = m_BaseScenes->at(i)->GetDescription();
	}
}

void TowerDefense::Base::UpdateActivityDescription()
{
	if (m_ActivityText.size() < 1)
		return;

	if (m_ActivityDescription->GetMessage() != m_ActivityText)
	{
		m_ActivityDescription = std::make_unique<Text>(m_ActivityText, 400.0f, 235.0f, 12.0f, 0.0f);
		m_ActivityDescription->SetPosition(400.0f, 235.0f, 0);
		m_ActivityDescription->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void TowerDefense::Base::UpdateViewDeck()
{
	Player& player = Player::Get();
	auto deck = player.GetDeck();
	player.UpdateDeckButton();
	if (player.DeckButtonClicked())
	{
		deck->Show(!deck->IsShowing());
	}
	deck->Update();
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