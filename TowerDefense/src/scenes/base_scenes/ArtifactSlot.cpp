#include "pch.h"
#include "ArtifactSlot.h"
#include "core/Player.h"

TowerDefense::ArtifactSlot::ArtifactSlot(float x, float y, std::shared_ptr<Artifact> artifact, int price)
	:m_Price(price), m_ShowingInfo(false), m_Artifact(artifact),
	m_PriceText(std::make_unique<Text>(std::to_string(price), x - 10.0f, y - 50.0f, 12.0f, 0.0f)),
	m_GoldImage(std::make_unique<Image>("goldIcon", x + 20.0f, y - 50.0f, 20, 20, 0.0f)),
	m_Fade(std::make_unique<Rectangle>(400.0f, 300.0f, 800.0f, 600.0f))
{
	m_Artifact->SetX(x);
	m_Artifact->SetY(y);
	m_Fade->SetColor(0.0f, 0.0f, 0.0f, .95f);
	m_PriceText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::ArtifactSlot::Render()
{
	m_Artifact->Render();
	m_PriceText->Render();
	m_GoldImage->Render();

	if (m_ShowingInfo)
	{
		m_Fade->Render();
		m_Artifact->RenderArtifactDetails();
	}
}

void TowerDefense::ArtifactSlot::Update()
{
	if (m_ShowingInfo)
	{
		if (Input::GetLeftMouseClickedAndSetFalse() || Input::GetRightMouseClickedAndSetFalse())
			m_ShowingInfo = false;
		return;
	}


	if (m_Artifact->Contains(Input::GetMouseX(), Input::GetMouseY()))
	{
		if (Input::GetLeftMouseClickedAndSetFalse())
		{
			Player& player = Player::Get();
			if (player.GetResource(Resource::GOLD) > m_Price)
			{
				player.ChangeResource(-m_Price, Resource::GOLD);
				player.AddToArtifacts(m_Artifact);
				m_Artifact.reset();
			}
		}
		else if (Input::GetRightMouseClickedAndSetFalse())
			m_ShowingInfo = true;
	}
}