#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "scenes/InGameSettings.h"

TowerDefense::Temple::Temple()
	:BaseScene("meditateButton", "Strengthen your resolve", 0),
	m_Tree(std::make_shared<HolyPower>(1, nullptr)),
	m_BackToCamp(std::make_unique<Button>(690.0f, 60.0f, 180, 50, "returnToCampButton"))
{
	auto damage2 = std::make_shared<HolyPower>(2, m_Tree);
	auto damage3 = std::make_shared<HolyPower>(3, damage2);
	damage3->AddChild(std::make_shared<TempleLevel10>(damage3));
	damage2->AddChild(damage3);
	m_Tree->AddChild(damage2);

	m_Tree->SetPosition(400.0f, 450.0f, 400.0f);
}

void TowerDefense::Temple::Render()
{
	m_BackToCamp->Render();

	m_Tree->Render();
	if (m_Tree->GetSelectedSkill())
		m_Tree->GetSelectedSkill()->RenderInfo();

	Player& player = Player::Get();
	InGameSettings::Get().RenderButton();
	player.RenderStats();
	player.RenderDeckAndArtifacts();
	if (InGameSettings::Get().IsShowing())
		InGameSettings::Get().Render();
}

void TowerDefense::Temple::Update()
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

	m_BackToCamp->Update();
	m_Tree->Update();
	if (m_BackToCamp->IsClicked())
		m_Exit = true;
}

void TowerDefense::Temple::OnSwitch()
{
	BaseScene::OnSwitch();
}