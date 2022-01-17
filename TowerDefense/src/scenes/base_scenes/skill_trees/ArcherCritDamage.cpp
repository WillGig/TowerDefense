#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "Auras/Aura.h"

TowerDefense::ArcherCritDamage::ArcherCritDamage(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("ArcherCritDamageSkill", "Crit Damage", 400, parent)
{
	m_InfoText = std::make_unique<Text>("Archer and Rangers\ngain 50% Crit damage\n\nCost: 400 Gold", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::ArcherCritDamage::Apply()
{
	Player::Get().AddCombatAura(std::make_shared<Aura::ArcherCritDamage>(0.5f));
}