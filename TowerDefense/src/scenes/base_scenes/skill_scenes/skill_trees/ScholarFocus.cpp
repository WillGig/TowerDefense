#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "auras/Aura.h"

TowerDefense::ScholarFocus::ScholarFocus(int level, std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("FocusSkill" + std::to_string(level), "Scholar Focus " + std::to_string(level), 300, parent)
{
	m_InfoText = std::make_unique<Text>("Scholars generate an\nadditional focus.", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::ScholarFocus::Apply()
{
	Player::Get().AddCombatAura(std::make_shared<Aura::ScholarFocus>(1));
}