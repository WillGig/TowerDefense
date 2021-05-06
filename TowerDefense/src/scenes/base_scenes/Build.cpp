#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "scenes/Base.h"

TowerDefense::Build::Build()
	:BaseScene("buildButton", "Create something new."),
	m_Cancel(std::make_unique<Button>(690.0f, 125.0f, 180, 50, "cancelButton")),
	m_Buttons(std::make_unique<std::vector<std::shared_ptr<BuildButton>>>())
{
}

void TowerDefense::Build::Render()
{
	Player& player = Player::Get();
	player.RenderDeckButton();
	player.RenderArtifactsPile();
	player.RenderStats();
	m_Cancel->Render();

	for (unsigned int i = 0; i < m_Buttons->size(); i++)
		m_Buttons->at(i)->Render();

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

void TowerDefense::Build::Update()
{
	Player& player = Player::Get();

	if (!player.GetSelectedDeckCard() && !player.ArtifactsShowing())
	{
		player.UpdateDeckButton();
		if (player.DeckButtonClicked())
			player.ToggleDeckShow();
	}

	if (player.DeckShowing())
		player.UpdateDeck();
	else
	{
		player.UpdateArtifactsPile();
		if (!player.ArtifactsShowing())
		{
			for (unsigned int i = 0; i < m_Buttons->size(); i++)
			{
				m_Buttons->at(i)->Update();
				if (m_Buttons->at(i)->Clicked())
				{
					if (player.GetGold() >= m_Buttons->at(i)->GetCost())
					{
						player.ChangeGold(-m_Buttons->at(i)->GetCost());
						Base::AddBaseScene(m_Buttons->at(i)->GetScene());
						m_Exit = true;
					}
				}
			}

			m_Cancel->Update();
			if (m_Cancel->IsClicked())
				m_Exit = true;
		}
	}
}

void TowerDefense::Build::OnSwitch()
{
	BaseScene::OnSwitch();
	m_Buttons->clear();
	if(!Base::ContainsScene("Library"))
		AddBuildButton(std::make_shared<BuildButton>("buildLibrary", 500, std::make_shared<Library>()));
	//if (!Base::ContainsScene("Fishing"))
	//	AddBuildButton(BuildButton("buildFishery", 500, std::make_shared<Fishing>()));
	if (!Base::ContainsScene("Chapel"))
		AddBuildButton(std::make_shared<BuildButton>("buildChapel", 1000, std::make_shared<Chapel>()));
	if (!Base::ContainsScene("Smithing"))
		AddBuildButton(std::make_shared<BuildButton>("buildSmithy", 1000, std::make_shared<Smithing>()));
	if (!Base::ContainsScene("Tavern"))
		AddBuildButton(std::make_shared<BuildButton>("buildTavern", 2000, std::make_shared<Tavern>()));
}

void TowerDefense::Build::AddBuildButton(std::shared_ptr<BuildButton> button)
{
	int position = m_Buttons->size();
	button->SetPosition(400.0f, 367.0f - position * 33.0f);
	m_Buttons->push_back(button);
}
