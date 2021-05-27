#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"

TowerDefense::Trader::Trader()
	:BaseScene("tradeButton", "Let's make a deal."), m_LastRefresh(GetDay()), m_InfoCard(-1), m_InfoArtifact(), m_SpinEnd(0),
	m_Wood(std::make_unique<Button>(95.0f, 280.0f, 100, 40, "buyWoodButton")), 
	m_Stone(std::make_unique<Button>(95.0f, 215.0f, 100, 40, "buyStoneButton")),
	m_Wheat(std::make_unique<Button>(95.0f, 150.0f, 100, 40, "buyWheatButton")),
	m_Spin(std::make_unique<Button>(360.0f, 90.0f, 100, 40, "spinButton")),
	m_BackToCamp(std::make_unique<Button>(690.0f, 125.0f, 180, 50, "returnToCampButton")),
	m_WoodText(std::make_unique<Text>("300", 180.0f, 280.0f, 12.0f, 0.0f)), 
	m_StoneText(std::make_unique<Text>("300", 180.0f, 215.0f, 12.0f, 0.0f)),
	m_WheatText(std::make_unique<Text>("300", 180.0f, 150.0f, 12.0f, 0.0f)),
	m_SpinText(std::make_unique<Text>("100", 350.0f, 40.0f, 12.0f, 0.0f)),
	m_WoodGoldIcon(std::make_unique<Image>("goldIcon", 210.0f, 280.0f, 20, 20, 0.0f)),
	m_StoneGoldIcon(std::make_unique<Image>("goldIcon", 210.0f, 215.0f, 20, 20, 0.0f)),
	m_WheatGoldIcon(std::make_unique<Image>("goldIcon", 210.0f, 150.0f, 20, 20, 0.0f)),
	m_SpinGoldIcon(std::make_unique<Image>("goldIcon", 380.0f, 40.0f, 20, 20, 0.0f)),
	m_SpinWheel(std::make_unique<Image>("spinWheel", 360.0f, 230.0f, 200, 200, 0.0f)),
	m_SpinPicker(std::make_unique<Image>("spinPicker", 360.0f, 325.0f, 32, 32, 0.0f))
{
	m_WoodText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_StoneText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_WheatText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpinText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_Cards[0] = std::make_unique<CardSlot>(80.0f, 450.0f, Card::GetCommonCard(), (int)(Random::GetFloat()*50.0f + 100));
	m_Cards[1] = std::make_unique<CardSlot>(208.0f, 450.0f, Card::GetCommonCard(), (int)(Random::GetFloat() * 50.0f + 100));
	m_Cards[2] = std::make_unique<CardSlot>(336.0f, 450.0f, Card::GetCommonCard(), (int)(Random::GetFloat() * 50.0f + 100));
	m_Cards[3] = std::make_unique<CardSlot>(464.0f, 450.0f, Card::GetUncommonCard(), (int)(Random::GetFloat() * 50.0f + 150));
	m_Cards[4] = std::make_unique<CardSlot>(592.0f, 450.0f, Card::GetUncommonCard(), (int)(Random::GetFloat() * 50.0f + 150));
	m_Cards[5] = std::make_unique<CardSlot>(720.0f, 450.0f, Card::GetRareCard(), (int)(Random::GetFloat() * 50.0f + 200));
	
	m_Artifacts[0] = std::make_unique<ArtifactSlot>(520.0f, 280.0f, Artifact::GetRandomArtifact(), (int)(Random::GetFloat() * 50.0f + 200));
	m_Artifacts[1] = std::make_unique<ArtifactSlot>(620.0f, 280.0f, Artifact::GetRandomArtifact(), (int)(Random::GetFloat() * 50.0f + 200));
	m_Artifacts[2] = std::make_unique<ArtifactSlot>(720.0f, 280.0f, Artifact::GetRandomArtifact(), (int)(Random::GetFloat() * 50.0f + 200));
}

void TowerDefense::Trader::Render()
{
	Player& player = Player::Get();
	player.RenderStats();
	m_BackToCamp->Render();

	for (unsigned int i = 0; i < m_Cards.size(); i++)
	{
		if (m_Cards[i]->CardAvailable() && i != m_InfoCard)
			m_Cards[i]->Render();
	}

	for (unsigned int i = 0; i < m_Artifacts.size(); i++)
	{
		if (m_Artifacts[i]->ArtifactAvailable() && i != m_InfoArtifact)
			m_Artifacts[i]->Render();
	}

	m_Wood->Render();
	m_WoodText->Render();
	m_WoodGoldIcon->Render();
	m_Stone->Render();
	m_StoneText->Render();
	m_StoneGoldIcon->Render();
	m_Wheat->Render();
	m_WheatText->Render();
	m_WheatGoldIcon->Render();
	m_Spin->Render();
	m_SpinText->Render();
	m_SpinGoldIcon->Render();
	m_SpinWheel->Render();
	m_SpinPicker->Render();

	if (m_InfoCard == -1 && m_InfoArtifact == -1)
		player.RenderDeckAndArtifacts();
	else if (m_InfoArtifact == -1)
		m_Cards[m_InfoCard]->Render();
	else
		m_Artifacts[m_InfoArtifact]->Render();
}

void TowerDefense::Trader::Update()
{
	Player& player = Player::Get();

	FindInfo();

	if(m_InfoCard == -1 && m_InfoArtifact == -1)
		player.UpdateDeckAndArtifacts();

	if (!player.DeckShowing() && !player.ArtifactsShowing())
	{
		if (m_InfoCard != -1)
			m_Cards[m_InfoCard]->Update();
		else if (m_InfoArtifact != -1)
			m_Artifacts[m_InfoArtifact]->Update();
		else
		{
			for (unsigned int i = 0; i < m_Cards.size(); i++)
			{
				if (m_Cards[i]->CardAvailable())
					m_Cards[i]->Update();
			}

			for (unsigned int i = 0; i < m_Artifacts.size(); i++)
			{
				if (m_Artifacts[i]->ArtifactAvailable())
					m_Artifacts[i]->Update();
			}

			Player& player = Player::Get();

			m_Wood->Update();
			if (m_Wood->IsClicked() && player.GetResource(Resource::GOLD) > 299)
			{
				player.ChangeResource(-300, Resource::GOLD);
				player.ChangeResource(100, Resource::WOOD);
			}

			m_Stone->Update();
			if (m_Stone->IsClicked() && player.GetResource(Resource::GOLD) > 299)
			{
				player.ChangeResource(-300, Resource::GOLD);
				player.ChangeResource(100, Resource::STONE);
			}

			m_Wheat->Update();
			if (m_Wheat->IsClicked() && player.GetResource(Resource::GOLD) > 299)
			{
				player.ChangeResource(-300, Resource::GOLD);
				player.ChangeResource(100, Resource::WHEAT);
			}

			m_Spin->Update();
			if (m_Spin->IsClicked() && player.GetResource(Resource::GOLD) > 99 && m_SpinWheel->GetRotation() == m_SpinEnd)
			{
				m_SpinEnd = (int)(m_SpinWheel->GetRotation() - 720 - (int)(Random::GetFloat() * 360.0f));
				player.ChangeResource(-100, Resource::GOLD);
			}

			int rot = (int)m_SpinWheel->GetRotation();
			if (rot > m_SpinEnd)
			{
				rot--;
				if (m_SpinEnd - rot < -240)
					rot--;
				if (m_SpinEnd - rot < -180)
					rot--;
				if (m_SpinEnd - rot < -120)
					rot--;
				if (m_SpinEnd - rot < -60)
					rot--;

				m_SpinWheel->SetRotation((float)rot);
				if (rot == m_SpinEnd)
				{
					if (rot % 360 > -60)
						player.ChangeHealth(-10);	
					else if (rot % 360 > -120)
						player.ChangeResource(50, Resource::STONE);
					else if (rot % 360 > -180)
						player.ChangeResource(50, Resource::WHEAT);
					else if (rot % 360 > -240)
						player.ChangeResource(300, Resource::GOLD);
					else if (rot % 360 > -300)
						player.ChangeResource(50, Resource::WOOD);
					else
						player.ChangeResource(100, Resource::GOLD);
				}
			}

			m_BackToCamp->Update();
			if (m_BackToCamp->IsClicked() && rot == m_SpinEnd)
				m_Exit = true;
		}
	}
}

void TowerDefense::Trader::OnSwitch()
{
	BaseScene::OnSwitch();

	if (GetDay() - m_LastRefresh > 4)
	{
		m_Cards[0] = std::make_unique<CardSlot>(80.0f, 450.0f, Card::GetCommonCard(), (int)(Random::GetFloat() * 50.0f + 100));
		m_Cards[1] = std::make_unique<CardSlot>(208.0f, 450.0f, Card::GetCommonCard(), (int)(Random::GetFloat() * 50.0f + 100));
		m_Cards[2] = std::make_unique<CardSlot>(336.0f, 450.0f, Card::GetCommonCard(), (int)(Random::GetFloat() * 50.0f + 100));
		m_Cards[3] = std::make_unique<CardSlot>(464.0f, 450.0f, Card::GetUncommonCard(), (int)(Random::GetFloat() * 50.0f + 150));
		m_Cards[4] = std::make_unique<CardSlot>(592.0f, 450.0f, Card::GetUncommonCard(), (int)(Random::GetFloat() * 50.0f + 150));
		m_Cards[5] = std::make_unique<CardSlot>(720.0f, 450.0f, Card::GetRareCard(), (int)(Random::GetFloat() * 50.0f + 200));

		m_Artifacts[0] = std::make_unique<ArtifactSlot>(520.0f, 280.0f, Artifact::GetRandomArtifact(), (int)(Random::GetFloat() * 50.0f + 200));
		m_Artifacts[1] = std::make_unique<ArtifactSlot>(620.0f, 280.0f, Artifact::GetRandomArtifact(), (int)(Random::GetFloat() * 50.0f + 200));
		m_Artifacts[2] = std::make_unique<ArtifactSlot>(720.0f, 280.0f, Artifact::GetRandomArtifact(), (int)(Random::GetFloat() * 50.0f + 200));
		
		m_LastRefresh = GetDay();
	}
}

void TowerDefense::Trader::FindInfo()
{
	m_InfoCard = -1; 
	m_InfoArtifact = -1;

	for (unsigned int i = 0; i < m_Cards.size(); i++)
	{
		if (m_Cards[i]->ShowingInfo())
		{
			m_InfoCard = i;
			return;
		}
	}
	
	for (unsigned int i = 0; i < m_Artifacts.size(); i++)
	{
		if (m_Artifacts[i]->ShowingInfo())
		{
			m_InfoArtifact = i;
			return;
		}
	}
}