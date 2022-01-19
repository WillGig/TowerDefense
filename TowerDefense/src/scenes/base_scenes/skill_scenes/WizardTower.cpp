#include "pch.h"
#include "SkillScene.h"
#include "core/Player.h"
#include "scenes/InGameSettings.h"

TowerDefense::WizardTower::WizardTower()
	:SkillScene("studyButton", "Conduct your research", 0)
{
	m_Tree = std::make_shared<WizardDamage>(1, nullptr);

	auto damage2 = std::make_shared<WizardDamage>(2, m_Tree);
	auto damage3 = std::make_shared<WizardDamage>(3, damage2);
	damage3->AddChild(std::make_shared<WizardLevel10>(damage3));
	damage2->AddChild(damage3);
	m_Tree->AddChild(damage2);

	m_Tree->SetPosition(400.0f, 450.0f, 400.0f);
}