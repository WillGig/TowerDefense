#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "auras/Aura.h"

TowerDefense::AlchemistDamage::AlchemistDamage(int level, std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("DamageSkill" + std::to_string(level), "Alchemist Damage " + std::to_string(level), 300, parent)
{
	m_InfoText = std::make_unique<Text>("Increase Alchemist\ndamage by 1", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::AlchemistDamage::Apply()
{
	Player::Get().AddCombatAura(std::make_shared<Aura::AlchemistDamage>(1.0f));
}