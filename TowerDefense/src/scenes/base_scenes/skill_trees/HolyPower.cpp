#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "auras/Aura.h"

TowerDefense::HolyPower::HolyPower(int level, std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("DamageSkill" + std::to_string(level), "Holy Power " + std::to_string(level), 300, parent)
{
	m_InfoText = std::make_unique<Text>("Paladins and Clerics\ngain +1 Magic", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::HolyPower::Apply()
{
	Player::Get().AddCombatAura(std::make_shared<Aura::HolyPower>(1.0f));
}