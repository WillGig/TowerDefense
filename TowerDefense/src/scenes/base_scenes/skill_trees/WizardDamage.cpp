#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "auras/Aura.h"

TowerDefense::WizardDamage::WizardDamage(int level, std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("ArcherDamageSkill" + std::to_string(level), "Wizard Damage " + std::to_string(level), 300, parent)
{
	m_InfoText = std::make_unique<Text>("Increase Archer and\nRanger damage by 1", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::WizardDamage::Apply()
{
	//Player::Get().AddCombatAura(std::make_shared<Aura::ArcherDamage>(1.0f));
}