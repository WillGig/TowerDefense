#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "auras/Aura.h"

TowerDefense::ArcherLevel10::ArcherLevel10(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("Level10Skill", "Archer Level 10 ", 500, parent)
{
	m_InfoText = std::make_unique<Text>("Unlock level 10\nArcher and Ranger\n\nCost: 500 Gold", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::ArcherLevel10::Apply()
{
	//TODO: Level 10 upgrades
}