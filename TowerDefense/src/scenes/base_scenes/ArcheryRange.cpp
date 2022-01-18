#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "skill_trees/SkillTreeSkill.h"
#include "scenes/InGameSettings.h"

TowerDefense::ArcheryRange::ArcheryRange()
	:BaseScene("archeryButton", "Practice your aim", 0),
	m_Tree(std::make_shared<ArcherDamage>(1, nullptr)),
	m_BackToCamp(std::make_unique<Button>(690.0f, 60.0f, 180, 50, "returnToCampButton"))
{
	auto multi1 = std::make_shared<MultiShot>(1, m_Tree);
	multi1->AddChild(std::make_shared<MultiShot>(2, multi1));
	m_Tree->AddChild(multi1);

	auto damage2 = std::make_shared<ArcherDamage>(2, m_Tree);
	auto damage3 = std::make_shared<ArcherDamage>(3, damage2);
	damage3->AddChild(std::make_shared<ArcherLevel10>(damage3));
	damage2->AddChild(damage3);
	m_Tree->AddChild(damage2);

	auto critChance1 = std::make_shared<ArcherCritChance>(1, m_Tree);
	auto critChance2 = std::make_shared<ArcherCritChance>(2, critChance1);
	critChance2->AddChild(std::make_shared<ArcherCritChance>(3, critChance2));
	auto critDamage1 = std::make_shared<ArcherCritDamage>(1, critChance1);
	critDamage1->AddChild(std::make_shared<ArcherCritDamage>(2, critDamage1));
	critChance1->AddChild(critChance2);
	critChance1->AddChild(critDamage1);
	m_Tree->AddChild(critChance1);

	m_Tree->SetPosition(400.0f, 450.0f, 400.0f);
}

void TowerDefense::ArcheryRange::Render()
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

void TowerDefense::ArcheryRange::Update()
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

void TowerDefense::ArcheryRange::OnSwitch()
{
	BaseScene::OnSwitch();
}