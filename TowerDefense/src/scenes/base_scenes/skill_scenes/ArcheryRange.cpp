#include "pch.h"
#include "SkillScene.h"
#include "core/Player.h"
#include "scenes/InGameSettings.h"

TowerDefense::ArcheryRange::ArcheryRange()
	:SkillScene("archeryButton", "Practice your aim", 3)
{
	m_Tree = std::make_shared<ArcherDamage>(1, nullptr);

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