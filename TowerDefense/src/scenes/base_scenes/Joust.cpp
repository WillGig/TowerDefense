#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"

TowerDefense::Joust::Joust()
	:BaseScene("joustButton", "Test your skills", 3), m_Distance(500), m_Winner(-1), m_Level(1), m_CircleSpawn(30), m_Jousting(false), m_Failed(false),
	m_BackToCamp(std::make_unique<Button>(400.0f, 100.0f, 180, 50, "returnToCampButton")),
	m_Joust(std::make_unique<Button>(400.0f, 100.0f, 180, 50, "joustButton")),
	m_Player(std::make_unique<Image>("knight", 150.0f, 350.0f, 150, 100, 0.0f)),
	m_Knight(std::make_unique<Image>("blackKnight", 650.0f, 350.0f, 150, 100, 0.0f)),
	m_LevelText(std::make_unique<Text>("Level: 1", 400.0f, 450.0f, 24.0f, 0.0f))
{
	m_LevelText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::Joust::Render()
{
	Player& player = Player::Get();
	player.RenderStats();

	if(m_Winner != 1)
		m_Player->Render();
	if(m_Winner != 0)
		m_Knight->Render();
	m_LevelText->Render();

	if(!m_Jousting && m_Winner == -1)
		m_Joust->Render();
	else if (!m_Jousting)
	{
		if (m_Winner == 0)
			m_Joust->Render();
		m_WinnerMessage->Render();
		m_BackToCamp->Render();
	}
	else
	{
		for (unsigned int i = 0; i < m_Circles.size(); i++)
			m_Circles[i].Render();
	}
	
	player.RenderDeckAndArtifacts();
}

void TowerDefense::Joust::Update()
{
	Player& player = Player::Get();

	player.UpdateDeckAndArtifacts();

	if (!player.DeckShowing() && !player.ArtifactsShowing())
	{

		if (m_Jousting)
		{
			//Update all circles and check if a circle was missed
			for (unsigned int i = 0; i < m_Circles.size(); i++)
			{
				m_Circles[i].Update();
				if (m_Circles[i].Remove())
				{
					if (!m_Circles[i].Clicked())
						m_Failed = true;
					m_RemoveCircles.push_back(i);
				}
			}

			//Remove all clicked and missed circles
			for (unsigned int i = 0; i < m_RemoveCircles.size(); i++)
				m_Circles.erase(m_Circles.begin() + m_RemoveCircles[i]);
			m_RemoveCircles.clear();

			//Move Jousters and add circles
			if (m_Distance > 100)
			{
				m_CircleSpawn--;
				if (m_CircleSpawn == 0 && m_Distance > 200)
				{
					m_Circles.emplace_back(Random::GetFloat() * 600.0f + 100.0f, Random::GetFloat() * 200.0f + 200.0f, Random::GetFloat() * 20.0f + (50.0f * 10.0f / (9.0f + m_Level)), Random::GetFloat() * 0.3f + 0.3f * ((9.0f + m_Level) / 10.0f));
					m_CircleSpawn = 60 - (int)(20.0f * ((9.0f + m_Level) / 10.0f));
				}
					
				Vec3 posPlayer = m_Player->GetPosition();
				m_Player->SetPosition(posPlayer.x + 1, posPlayer.y, posPlayer.z);
				Vec3 posKnight = m_Knight->GetPosition();
				m_Knight->SetPosition(posKnight.x - 1, posKnight.y, posKnight.z);
				m_Distance = (int)(posKnight.x - posPlayer.x);
			}
			else
			{
				//Determine winner and set victory text

				if (m_Circles.size() > 0)
					m_Failed = true;

				if (m_Failed)
					m_Winner = 1;
				else
					m_Winner = 0;
				if (m_Winner == 0)
				{
					m_WinnerMessage = std::make_unique<Text>("Victory! (+50 Gold)", 400.0f, 250.0f, 12.0f, 0.0f);
					m_WinnerMessage->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
					player.ChangeResource(50, Resource::GOLD);
				}
				else if (m_Winner == 1)
				{
					m_WinnerMessage = std::make_unique<Text>("Defeat! (-10 Health)", 400.0f, 250.0f, 12.0f, 0.0f);
					m_WinnerMessage->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
					player.ChangeHealth(-10);
				}
				m_Jousting = false;
			}
		}
		else if(m_Winner == -1)
		{
			m_Joust->Update();
			if (m_Joust->IsClicked())
			{
				m_Jousting = true;
				m_Joust->SetY(175.0f);
			}
		}
		else
		{
			if (m_Winner == 0)
			{
				m_Joust->Update();
				if (m_Joust->IsClicked())
				{
					m_Jousting = true;
					m_Winner = -1;
					m_Player->SetPosition(150.0f, 350.0f, 0.0f);
					m_Knight->SetPosition(650.0f, 350.0f, 0.0f);
					m_Circles.clear();
					m_RemoveCircles.clear();
					m_Distance = 500;
					m_Level++;
					m_LevelText = std::make_unique<Text>("Level: " + std::to_string(m_Level), 400.0f, 450.0f, 24.0f, 0.0f);
					m_LevelText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
					m_CircleSpawn = 30;
				}
			}

			m_BackToCamp->Update();
			if (m_BackToCamp->IsClicked())
			{
				m_Exit = true;
				m_ActivityReady = m_ActivityCoolDown;
			}
		}
	}
}

void TowerDefense::Joust::OnSwitch()
{
	BaseScene::OnSwitch();
	m_Jousting = false;
	m_Failed = false;
	m_Winner = -1;
	m_Player->SetPosition(150.0f, 350.0f, 0.0f);
	m_Knight->SetPosition(650.0f, 350.0f, 0.0f);
	m_Circles.clear();
	m_RemoveCircles.clear();
	m_Distance = 500;
	m_CircleSpawn = 30;
	m_Level = 1;
	m_LevelText = std::make_unique<Text>("Level: 1", 400.0f, 450.0f, 24.0f, 0.0f);
	m_LevelText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}
