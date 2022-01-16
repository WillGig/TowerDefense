#include "pch.h"
#include "SkillTreeSkill.h"

TowerDefense::TestSkill::TestSkill()
	:SkillTreeSkill("selectedTile", "Test Skill", 0, nullptr)
{
	m_InfoText = std::make_unique<Text>("This is a test skill\nthat does something", 0.0f, 0.0f, 12.0f, 190.0f);
}

TowerDefense::TestSkill::TestSkill(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("selectedTile", "Test Skill", 0, parent)
{
	m_InfoText = std::make_unique<Text>("This is a test skill\nthat does something", 0.0f, 0.0f, 12.0f, 190.0f);
}


void TowerDefense::TestSkill::Apply()
{

}