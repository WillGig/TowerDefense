#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "Auras/Aura.h"

TowerDefense::ArcherCritChance::ArcherCritChance(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("ArcherCritChanceSkill", "Crit Chance", 200, parent)
{
	m_InfoText = std::make_unique<Text>("Archer and Rangers\ngain 20% Crit chance\n\nCost: 200 Gold", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::ArcherCritChance::Apply()
{
	Player::Get().AddCombatAura(std::make_shared<Aura::ArcherCritChance>(0.2f));
}