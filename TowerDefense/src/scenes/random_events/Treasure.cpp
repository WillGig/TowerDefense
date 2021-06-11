#include "pch.h"
#include "RandomEvent.h"
#include "core/Player.h"

TowerDefense::Treasure::Treasure()
	:m_Image(std::make_unique<Image>("events/Treasure", 200.0f, 350.0f, 300, 300, 0.0f)),
	m_Continue(std::make_unique<Button>(400.0f, 100.0f, 180, 50, "continueButton")),
	m_Gold(std::make_unique<ResourceReward>((int)(Random::GetFloat() * 300), Resource::GOLD)),
	m_Artifact(std::make_unique<ArtifactReward>())
{
	std::string text = "You find treasure!\n";

	m_Prompt = std::make_unique<Text>(text, 550.0f, 450.0f, 16.0f, 0.0f);
	m_Prompt->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_Gold->SetPosition(550.0f, 350.0f);
	m_Artifact->SetPosition(550.0f, 300.0f);
}

void TowerDefense::Treasure::Render()
{
	m_Image->Render();
	m_Prompt->Render();
	m_Continue->Render();
	if(m_Gold)
		m_Gold->Render();
	if(m_Artifact)
		m_Artifact->Render();
}

void TowerDefense::Treasure::Update()
{
	if (m_Artifact)
	{
		m_Artifact->Update();

		if (m_Artifact->RewardTaken())
			m_Artifact.reset();
		else if (m_Artifact->RequiresFocus())
			return;
	}

	m_Continue->Update();
	if (m_Continue->IsClicked())
		m_Exit = true;

	if (m_Gold)
	{
		m_Gold->Update();
		if (m_Gold->RewardTaken())
		{
			m_Gold.reset();
			if (m_Artifact)
				m_Artifact->SetPosition(550.0f, 350.0f);
		}
	}	
}