#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "auras/Aura.h"

TowerDefense::ArcherDamage::ArcherDamage(int level, std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("DamageSkill" + std::to_string(level), "Archer Damage " + std::to_string(level), parent)
{
	m_InfoText = std::make_unique<Text>("Increase Archer and\nRanger damage by 1", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::ArcherDamage::Apply()
{
	Player::Get().AddCombatAura(std::make_shared<Aura::ArcherDamage>(1.0f));
}