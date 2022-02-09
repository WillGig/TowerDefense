#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "auras/Aura.h"

TowerDefense::MusicPower::MusicPower(int level, std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("DamageSkill" + std::to_string(level), "Music Power " + std::to_string(level), parent)
{
	m_InfoText = std::make_unique<Text>("Bards\ngain +1 Magic", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::MusicPower::Apply()
{
	Player::Get().AddCombatAura(std::make_shared<Aura::MusicPower>(1.0f));
}