#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "skill_trees/SkillTreeSkill.h"

TowerDefense::ArcheryRange::ArcheryRange()
	:BaseScene("archeryButton", "Practice your aim", 0),
	m_Tree(std::make_shared<TestSkill>()),
	m_BackToCamp(std::make_unique<Button>(690.0f, 60.0f, 180, 50, "returnToCampButton"))
{
	m_Tree->AddChild(std::make_shared<TestSkill>(m_Tree));
	auto child = std::make_shared<TestSkill>(m_Tree);
	auto child2 = std::make_shared<TestSkill>(child);
	child2->AddChild(std::make_shared<TestSkill>(child2));
	child2->AddChild(std::make_shared<TestSkill>(child2));
	child->AddChild(child2);
	child->AddChild(std::make_shared<TestSkill>(child));
	m_Tree->AddChild(child);
	m_Tree->SetPosition(400.0f, 400.0f, 600.0f);
}

void TowerDefense::ArcheryRange::Render()
{
	Player& player = Player::Get();
	player.RenderStats();

	m_BackToCamp->Render();

	m_Tree->Render();
	if (m_Tree->GetSelectedSkill())
		m_Tree->GetSelectedSkill()->RenderInfo();

	player.RenderDeckAndArtifacts();
}

void TowerDefense::ArcheryRange::Update()
{
	Player& player = Player::Get();
	player.UpdateDeckAndArtifacts();

	if (!player.DeckShowing() && !player.ArtifactsShowing())
	{
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