#include "pch.h"
#include "CombatReward.h"
#include "core/Player.h"

TowerDefense::CombatReward::CombatReward(const std::string msg)
	:Button(0.0f, 0.0f, 180, 50, "CombatReward"),
	m_Text(std::make_unique<Text>(msg, 0.0f, 0.0f, 12.0f, 0.0f)), 
	m_RewardTaken(false), m_RequiresFocus(false), m_ShowingInfo(false)
{
	m_Text->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::CombatReward::Render()
{
	Button::Render();
	m_Text->Render();
}

void TowerDefense::CombatReward::Update()
{
	Button::Update();
	if (IsClicked())
		OnClicked();
	else if (Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetRightMouseClickedAndSetFalse())
		OnRightClicked();
}

void TowerDefense::CombatReward::SetPosition(float x, float y)
{
	Button::SetX(x);
	Button::SetY(y);
	m_Text->SetPosition(x, y, 0.0f);
}

TowerDefense::ResourceReward::ResourceReward(int amount, Resource type)
	:CombatReward(std::to_string(amount)), m_Amount(amount), m_Type(type)
{
	if(type == Resource::WOOD)
		m_Image = std::make_unique<Image>("woodIcon", 0.0f, 0.0f, 24, 24, 0.0f);
	else if (type == Resource::STONE)
		m_Image = std::make_unique<Image>("stoneIcon", 0.0f, 0.0f, 24, 24, 0.0f);
	else if (type == Resource::WHEAT)
		m_Image = std::make_unique<Image>("wheatIcon", 0.0f, 0.0f, 24, 24, 0.0f);
	else if (type == Resource::GOLD)
		m_Image = std::make_unique<Image>("goldIcon", 0.0f, 0.0f, 24, 24, 0.0f);
}

void TowerDefense::ResourceReward::Render()
{
	CombatReward::Render();
	m_Image->Render();
}

void TowerDefense::ResourceReward::OnClicked()
{
	Player::Get().ChangeResource(m_Amount, m_Type);
	m_RewardTaken = true;
}

void TowerDefense::ResourceReward::SetPosition(float x, float y)
{
	CombatReward::SetPosition(x, y);
	m_Image->SetPosition(x + 30, y - 2.0f, 0.0f);
}

TowerDefense::CardReward::CardReward(int numChoices)
	:CombatReward("Get a Card!"), m_CardChoice(std::make_unique<CardChoice>(numChoices, 0)),
	m_Confirm(std::make_unique<Button>(400.0f, 190.0f, 180, 50, "confirmButton")),
	m_Cancel(std::make_unique<Button>(690.0f, 125.0f, 180, 50, "cancelButton")),
	m_Fade(std::make_unique<Rectangle>(400.0f, 300.0f, 800.0f, 600.0f))
{
	m_Fade->SetColor(0.0f, 0.0f, 0.0f, 0.9f);
}

void TowerDefense::CardReward::Render()
{
	CombatReward::Render();

	if (m_RequiresFocus)
	{
		m_Fade->Render();
		Player& player = Player::Get();
		player.RenderStats();
		player.RenderDeckAndArtifacts();
		m_Cancel->Render();
		if (m_CardChoice->GetSelectedCard())
			m_Confirm->Render();
		m_CardChoice->Render();
	}
}

void TowerDefense::CardReward::Update()
{
	if (m_RequiresFocus)
	{
		m_ShowingInfo = m_CardChoice->ShowingInfo();
		if (!m_ShowingInfo)
		{
			m_Cancel->Update();
			if (m_Cancel->IsClicked())
				m_RequiresFocus = false;

			if (m_CardChoice->GetSelectedCard())
			{
				m_Confirm->Update();
				if (m_Confirm->IsClicked())
				{
					Player::Get().AddToDeck(m_CardChoice->GetSelectedCard());
					m_RequiresFocus = false;
					m_RewardTaken = true;
				}
			}
		}
		m_CardChoice->Update();
	}
	else
		CombatReward::Update();

}

void TowerDefense::CardReward::OnClicked()
{
	m_RequiresFocus = true;
}

TowerDefense::ArtifactReward::ArtifactReward()
	:CombatReward(""), m_Artifact(Artifact::GetRandomArtifact()),
	m_Image(std::make_unique<Image>(m_Artifact->GetName() , 0.0f, 0.0f, 32, 32, 0.0f)),
	m_Fade(std::make_unique<Rectangle>(400.0f, 300.0f, 800.0f, 600.0f))
{
	m_Fade->SetColor(0.0f, 0.0f, 0.0f, 0.9f);
}

void TowerDefense::ArtifactReward::Render()
{
	CombatReward::Render();
	m_Image->Render();
	if (m_RequiresFocus)
	{
		m_Fade->Render();
		m_Artifact->RenderArtifactDetails();
	}
}

void TowerDefense::ArtifactReward::Update()
{
	if (m_RequiresFocus)
	{
		if (Input::GetLeftMouseClickedAndSetFalse() || Input::GetRightMouseClickedAndSetFalse())
			m_RequiresFocus = false;
	}
	else
		CombatReward::Update();
}

void TowerDefense::ArtifactReward::SetPosition(float x, float y)
{
	CombatReward::SetPosition(x, y);
	m_Image->SetPosition(x, y, 0.0f);
}

void TowerDefense::ArtifactReward::OnClicked()
{
	Player::Get().AddToArtifacts(m_Artifact);
	m_RewardTaken = true;
}

void TowerDefense::ArtifactReward::OnRightClicked()
{
	m_RequiresFocus = true;
}