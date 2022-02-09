#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "auras/Aura.h"

TowerDefense::WizardDamage::WizardDamage(int level, std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("DamageSkill" + std::to_string(level), "Wizard Damage " + std::to_string(level), parent)
{
	m_InfoText = std::make_unique<Text>("Increase Wizard\ndamage by 1", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::WizardDamage::Apply()
{
	Player::Get().AddCombatAura(std::make_shared<Aura::WizardDamage>(1.0f));
}