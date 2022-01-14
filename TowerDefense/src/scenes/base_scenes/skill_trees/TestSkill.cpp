#include "pch.h"
#include "SkillTreeSkill.h"

TowerDefense::TestSkill::TestSkill()
	:SkillTreeSkill("selectedTile", nullptr)
{}

TowerDefense::TestSkill::TestSkill(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("selectedTile", parent)
{}


void TowerDefense::TestSkill::Apply()
{

}