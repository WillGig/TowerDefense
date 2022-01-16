#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "scenes/InGameSettings.h"

TowerDefense::GatherResources::GatherResources()
	:BaseScene("getResourcesButton", "Hard Work Pays Off.", 1), 
	m_AmountGathered(), m_CurrentActivity(Activity::MENU),
	m_Chop(std::make_unique<Button>(200.0f, 425.0f, 180, 50, "chopWoodButton")),
	m_Mine(std::make_unique<Button>(400.0f, 425.0f, 180, 50, "mineButton")),
	m_Farm(std::make_unique<Button>(600.0f, 425.0f, 180, 50, "farmButton")),
	m_Explore(std::make_unique<Button>(200.0f, 350.0f, 180, 50, "exploreButton")),
	m_BackToCamp(std::make_unique<Button>(400.0f, 200.0f, 180, 50, "returnToCampButton"))
{
}

void TowerDefense::GatherResources::Render()
{
	if (m_CurrentActivity == Activity::MENU)
	{
		m_Chop->Render();
		m_Mine->Render();
		m_Farm->Render();
		m_Explore->Render();
		m_BackToCamp->Render();
	}
	else if (m_CurrentActivity == Activity::CHOP || m_CurrentActivity == Activity::MINE || m_CurrentActivity == Activity::FARM)
	{
		m_Text->Render();
		m_BackToCamp->Render();
	}
	else if (m_CurrentActivity == Activity::EXPLORE)
	{
		m_Text->Render();
		m_BackToCamp->Render();
	}

	Player& player = Player::Get();
	InGameSettings::Get().RenderButton();
	player.RenderStats();
	player.RenderDeckAndArtifacts();
	if (InGameSettings::Get().IsShowing())
		InGameSettings::Get().Render();
}

void TowerDefense::GatherResources::Update()
{
	if (InGameSettings::Get().IsShowing())
	{
		InGameSettings::Get().Update();
		return;
	}

	Player& player = Player::Get();
	player.UpdateDeckAndArtifacts();

	if (player.DeckShowing() || player.ArtifactsShowing())
		return;

	InGameSettings::Get().UpdateButton();
	
	if (m_CurrentActivity == Activity::MENU)
	{
		m_Chop->Update();
		if (m_Chop->IsClicked())
		{
			m_CurrentActivity = Activity::CHOP;
			m_AmountGathered = Vec4i(player.GetResourceGatherRate(Resource::WOOD), 0, 0, 0);
			m_Text = std::make_unique<Text>("You manage to chop " + std::to_string(m_AmountGathered.w) + " wood", 400.0f, 300.0f, 12.0f, 0.0f);
			m_Text->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		m_Mine->Update();
		if (m_Mine->IsClicked())
		{
			m_CurrentActivity = Activity::MINE;
			m_AmountGathered = Vec4i(0, player.GetResourceGatherRate(Resource::STONE), 0, 0);
			m_Text = std::make_unique<Text>("You manage to mine " + std::to_string(m_AmountGathered.x) + " stone", 400.0f, 300.0f, 12.0f, 0.0f);
			m_Text->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		m_Farm->Update();
		if (m_Farm->IsClicked())
		{
			m_CurrentActivity = Activity::FARM;
			m_AmountGathered = Vec4i(0, 0, player.GetResourceGatherRate(Resource::WHEAT), 0);
			m_Text = std::make_unique<Text>("You manage to farm " + std::to_string(m_AmountGathered.y) + " wheat", 400.0f, 300.0f, 12.0f, 0.0f);
			m_Text->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		m_Explore->Update();
		if (m_Explore->IsClicked())
		{
			m_CurrentActivity = Activity::EXPLORE;
			m_AmountGathered = Vec4i();

			//Find random distribution of resources
			float wood = Random::GetFloat();
			float stone = Random::GetFloat();
			float wheat = Random::GetFloat();
			int gatherRate = player.GetResourceGatherRate(Resource::EXPLORE);
			m_AmountGathered.w = (int)round(wood / (wood + stone + wheat) * gatherRate);
			m_AmountGathered.x = (int)round(stone / (wood + stone + wheat) * gatherRate);
			m_AmountGathered.y = (int)round(wheat / (wood + stone + wheat) * gatherRate);

			//Ensure that exactly gatherRate resources are gathered
			if (m_AmountGathered.w + m_AmountGathered.x + m_AmountGathered.y > gatherRate)
			{
				if (m_AmountGathered.w > m_AmountGathered.x && m_AmountGathered.w > m_AmountGathered.y)
					m_AmountGathered.w--;
				else if (m_AmountGathered.x > m_AmountGathered.w && m_AmountGathered.x > m_AmountGathered.y)
					m_AmountGathered.x--;
				else
					m_AmountGathered.y--;
			}
			else if (m_AmountGathered.w + m_AmountGathered.x + m_AmountGathered.y < gatherRate)
			{
				if (m_AmountGathered.w > m_AmountGathered.x && m_AmountGathered.w > m_AmountGathered.y)
					m_AmountGathered.w++;
				else if (m_AmountGathered.x > m_AmountGathered.w && m_AmountGathered.x > m_AmountGathered.y)
					m_AmountGathered.x++;
				else
					m_AmountGathered.y++;
			}

			std::string text = "You manage to find the follow resources:\n\n";
			if (m_AmountGathered.w != 0)
				text += std::to_string(m_AmountGathered.w) + " wood\n";
			if (m_AmountGathered.x != 0)
				text += std::to_string(m_AmountGathered.x) + " stone\n";
			if (m_AmountGathered.y != 0)
				text += std::to_string(m_AmountGathered.y) + " wheat\n";

			m_Text = std::make_unique<Text>(text, 400.0f, 350.0f, 12.0f, 0.0f);
			m_Text->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		m_BackToCamp->Update();
		if (m_BackToCamp->IsClicked())
			m_Exit = true;
	}
	else if (m_CurrentActivity == Activity::CHOP || m_CurrentActivity == Activity::MINE || m_CurrentActivity == Activity::FARM)
	{
		m_BackToCamp->Update();
		if (m_BackToCamp->IsClicked())
		{
			if(m_CurrentActivity == Activity::CHOP)
				Player::Get().ChangeResource(m_AmountGathered.w, Resource::WOOD);
			else if (m_CurrentActivity == Activity::MINE)
				Player::Get().ChangeResource(m_AmountGathered.x, Resource::STONE);
			else if (m_CurrentActivity == Activity::FARM)
				Player::Get().ChangeResource(m_AmountGathered.y, Resource::WHEAT);
			m_Exit = true;
			m_ActivityReady = m_ActivityCoolDown;
		}
	}
	else if (m_CurrentActivity == Activity::EXPLORE)
	{
		m_BackToCamp->Update();
		if (m_BackToCamp->IsClicked())
		{
			Player::Get().ChangeResource(m_AmountGathered.w, Resource::WOOD);
			Player::Get().ChangeResource(m_AmountGathered.x, Resource::STONE);
			Player::Get().ChangeResource(m_AmountGathered.y, Resource::WHEAT);
			Player::Get().ChangeResource(m_AmountGathered.z, Resource::GOLD);
			m_Exit = true;
			m_ActivityReady = m_ActivityCoolDown;
		}
	}
}

void TowerDefense::GatherResources::OnSwitch()
{
	BaseScene::OnSwitch();
	m_CurrentActivity = Activity::MENU;
}