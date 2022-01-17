#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "Auras/Aura.h"

TowerDefense::MultiShot::MultiShot(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("MultiShotSkill", "Multishot", 250, parent)
{
	m_InfoText = std::make_unique<Text>("Archer's gain\n+1 Multishot\n\nCost: 250 Gold", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::MultiShot::Apply()
{
	Player::Get().AddCombatAura(std::make_shared<Aura::MultiShot>(1));
}