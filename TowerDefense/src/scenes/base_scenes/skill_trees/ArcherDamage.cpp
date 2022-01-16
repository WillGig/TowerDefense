#include "pch.h"
#include "SkillTreeSkill.h"
#include "core/Player.h"
#include "auras/Aura.h"

TowerDefense::ArcherDamage::ArcherDamage()
	:SkillTreeSkill("ArcherDamageSkill", "Archer Damage", 0, nullptr)
{
	m_InfoText = std::make_unique<Text>("Increase damage\nfrom Archers\nand Rangers by 1", 0.0f, 0.0f, 12.0f, 190.0f);
}

TowerDefense::ArcherDamage::ArcherDamage(std::shared_ptr<SkillTreeSkill> parent)
	: SkillTreeSkill("ArcherDamageSkill", "Archer Damage", 0, parent)
{
	m_InfoText = std::make_unique<Text>("Increase damage\nfrom Archers\nand Rangers by 1", 0.0f, 0.0f, 12.0f, 190.0f);
}

void TowerDefense::ArcherDamage::Apply()
{
	Player::Get().AddCombatAura(std::make_shared<Aura::ArcherDamage>(1.0f));
}