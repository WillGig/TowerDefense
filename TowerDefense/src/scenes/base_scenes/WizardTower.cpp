#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "scenes/InGameSettings.h"

TowerDefense::WizardTower::WizardTower()
	:BaseScene("studyButton", "Conduct your research", 0),
	m_Tree(std::make_shared<WizardDamage>(1, nullptr)),
	m_BackToCamp(std::make_unique<Button>(690.0f, 60.0f, 180, 50, "returnToCampButton"))
{
	auto damage2 = std::make_shared<WizardDamage>(2, m_Tree);
	auto damage3 = std::make_shared<WizardDamage>(3, damage2);
	damage3->AddChild(std::make_shared<WizardLevel10>(damage3));
	damage2->AddChild(damage3);
	m_Tree->AddChild(damage2);

	m_Tree->SetPosition(400.0f, 450.0f, 400.0f);
}

void TowerDefense::WizardTower::Render()
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

void TowerDefense::WizardTower::Update()
{
	if (InGameSettings::Get().IsShowing())
	{
		InGameSettings::Get().Update();
		return;
	}

	Player& player = Player::Get();
	player.UpdateDeckAndArtifacts();

	if (!player.DeckShowing() && !player.ArtifactsShowing())
	{
		InGameSettings::Get().UpdateButton();
		m_Tree->Update();
		m_BackToCamp->Update();
		if (m_BackToCamp->IsClicked())
			m_Exit = true;
	}
}

void TowerDefense::WizardTower::OnSwitch()
{
	BaseScene::OnSwitch();
}