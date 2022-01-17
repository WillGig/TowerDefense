#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "auras/Aura.h"

TowerDefense::ArcherDamage::ArcherDamage(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("ArcherDamageSkill", "Archer Damage", 300, parent)
{
	m_InfoText = std::make_unique<Text>("Increase Archer and\nRanger damage by 1\n\nCost: 300 Gold", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::ArcherDamage::Apply()
{
	Player::Get().AddCombatAura(std::make_shared<Aura::ArcherDamage>(1.0f));
}