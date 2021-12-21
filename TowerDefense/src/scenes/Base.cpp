#include "pch.h"
#include "Base.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "cards/HeroCard.h"
#include "core/SaveLoad.h"

int TowerDefense::Base::SaveSlot;

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::BaseScene>>> TowerDefense::Base::s_BaseScenes = std::make_shared<std::vector<std::shared_ptr<BaseScene>>>();

TowerDefense::Base::Base()
	:m_CurrentMenu(-1),
	m_NextDay(std::make_unique<Button>(600.0f, 175.0f, 180, 50, "nextDayButton")),
	m_Settings(std::make_unique<Button>(770.0f, 575.0f, 32, 32, "settingsIcon")),
	m_WaitText(std::make_unique<Text>("Available Again Tomorrow!", 400.0f, 235.0f, 12.0f, 0.0f))
{
	m_WaitText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
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
			{
				if (s_BaseScenes->at(i)->GetActivityReady() != 0)
					m_WaitText->Render();
				else
					s_BaseScenes->at(i)->RenderText();
			}
		}
		m_NextDay->Render();
		m_Settings->Render();
		player.RenderStats();
		player.RenderDeckAndArtifacts();
	}
	else
		s_BaseScenes->at(m_CurrentMenu)->Render();
}

void TowerDefense::Base::Update()
{
	if (m_CurrentMenu == -1)
	{
		m_Settings->Update();
		if (m_Settings->IsClicked())
		{
			//settings menu
		}

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
			m_CurrentMenu = -1;
	}
}

void TowerDefense::Base::OnSwitch()
{
	Save::SaveGame(SaveSlot);

	for (unsigned int i = 0; i < s_BaseScenes->size(); i++)
	{
		int ready = s_BaseScenes->at(i)->GetActivityReady();
		if (ready != 0)
			s_BaseScenes->at(i)->SetActivityReady(ready - 1);
	}
}

void TowerDefense::Base::Reset()
{
	s_BaseScenes = std::make_unique<std::vector<std::shared_ptr<BaseScene>>>();
	AddBaseScene(std::make_shared<GatherResources>());
	AddBaseScene(std::make_shared<Build>());
}

void TowerDefense::Base::CleanUp()
{
	s_BaseScenes.reset();
}

void TowerDefense::Base::UpdateActivities()
{
	for (unsigned int i = 0; i < s_BaseScenes->size(); i++)
	{
		s_BaseScenes->at(i)->UpdateButton();

		if (s_BaseScenes->at(i)->ButtonSelected() && s_BaseScenes->at(i)->GetActivityReady() != 0)
		{
			int ready = s_BaseScenes->at(i)->GetActivityReady();
			if(ready == 1)
				m_WaitText = std::make_unique<Text>("Available Again in 1 Day.", 400.0f, 235.0f, 12.0f, 0.0f);
			else
				m_WaitText = std::make_unique<Text>("Available Again in " + std::to_string(ready) + " Days.", 400.0f, 235.0f, 12.0f, 0.0f);
			m_WaitText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (s_BaseScenes->at(i)->ButtonClicked() && s_BaseScenes->at(i)->GetActivityReady() == 0)
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
		if (Random::GetFloat() > 0.25f)
			SetScene(SceneType::PRECOMBAT);
		else
			SetScene(SceneType::EVENT);
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