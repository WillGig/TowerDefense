#include "pch.h"
#include "Base.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "cards/HeroCard.h"

std::unique_ptr<std::vector<std::shared_ptr<TowerDefense::BaseScene>>> TowerDefense::Base::s_BaseScenes = std::make_unique<std::vector<std::shared_ptr<BaseScene>>>();

TowerDefense::Base::Base()
	:m_CurrentMenu(-1), m_ActivityDone(false),
	m_NextDay(std::make_unique<Button>(600.0f, 175.0f, 180, 50, "nextDayButton"))
{
	AddBaseScene(std::make_shared<Rest>());
	AddBaseScene(std::make_shared<Caves>());
	AddBaseScene(std::make_shared<Build>());
}

void TowerDefense::Base::Render()
{
	Player& player = Player::Get();

	if (m_CurrentMenu == -1)
	{
		for (unsigned int i = 0; i < s_BaseScenes->size(); i++)
		{
			s_BaseScenes->at(i)->RenderButton();
			if (s_BaseScenes->at(i)->ButtonSelected())
				s_BaseScenes->at(i)->RenderText();
		}
		m_NextDay->Render();
		player.RenderStats();
		player.RenderDeckAndArtifacts();
	}
	else
	{
		s_BaseScenes->at(m_CurrentMenu)->Render();
	}
}

void TowerDefense::Base::Update()
{
	if (m_CurrentMenu == -1)
	{
		Player& player = Player::Get();
		player.UpdateDeckAndArtifacts();

		if (!player.DeckShowing() && !player.ArtifactsShowing())
		{
			UpdateActivities();
			UpdateNextDay();
		}
	}
	else
	{
		s_BaseScenes->at(m_CurrentMenu)->Update();
		if (s_BaseScenes->at(m_CurrentMenu)->Exit())
		{
			m_ActivityDone = s_BaseScenes->at(m_CurrentMenu)->ActivityDone();
			m_CurrentMenu = -1;
		}
	}
}

void TowerDefense::Base::OnSwitch()
{
	m_ActivityDone = false;
}

void TowerDefense::Base::CleanUp()
{
	s_BaseScenes.reset();
}

void TowerDefense::Base::UpdateActivities()
{
	if (m_ActivityDone)
		return;

	for (unsigned int i = 0; i < s_BaseScenes->size(); i++)
	{
		s_BaseScenes->at(i)->UpdateButton();
		if (s_BaseScenes->at(i)->ButtonClicked())
		{
			m_CurrentMenu = i;
			s_BaseScenes->at(i)->OnSwitch();
			return;
		}
	}
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
	int position = s_BaseScenes->size();
	scene->SetButtonPosition((position % 3) *200.0f + 200.0f, 425 - (position/3) * 70.0f);
	s_BaseScenes->push_back(scene);
}

bool TowerDefense::Base::ContainsScene(const std::string& name)
{
	for (unsigned int i = 0; i < s_BaseScenes->size(); i++)
	{
		if (s_BaseScenes->at(i)->GetName() == name)
			return true;
	}
	return false;
}