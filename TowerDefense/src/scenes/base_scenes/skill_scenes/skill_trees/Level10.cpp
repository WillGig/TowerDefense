#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "auras/Aura.h"

TowerDefense::ArcherLevel10::ArcherLevel10(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("Level10Skill", "Archer Level 10 ", 500, parent)
{
	m_InfoText = std::make_unique<Text>("Unlock level 10\nArcher and Ranger", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::ArcherLevel10::Apply()
{
	//TODO: Level 10 upgrades
}

TowerDefense::WizardLevel10::WizardLevel10(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("Level10Skill", "Wizard Level 10 ", 500, parent)
{
	m_InfoText = std::make_unique<Text>("Unlock level 10\nWizard", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::WizardLevel10::Apply()
{
	//TODO: Level 10 upgrades
}

TowerDefense::TempleLevel10::TempleLevel10(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("Level10Skill", "Temple Level 10 ", 500, parent)
{
	m_InfoText = std::make_unique<Text>("Unlock level 10\nPaladin and Monk", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::TempleLevel10::Apply()
{
	//TODO: Level 10 upgrades
}

TowerDefense::MusicHallLevel10::MusicHallLevel10(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("Level10Skill", "Music Hall Level 10 ", 500, parent)
{
	m_InfoText = std::make_unique<Text>("Unlock level 10\nBard", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::MusicHallLevel10::Apply()
{
	//TODO: Level 10 upgrades
}

TowerDefense::AlchemyLabLevel10::AlchemyLabLevel10(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("Level10Skill", "Alchemy Lab Level 10 ", 500, parent)
{
	m_InfoText = std::make_unique<Text>("Unlock level 10\nAlchemist", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::AlchemyLabLevel10::Apply()
{
	//TODO: Level 10 upgrades
}