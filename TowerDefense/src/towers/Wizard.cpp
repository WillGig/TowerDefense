#include "pch.h"
#include "Wizard.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "cards/upgrades/Upgrades.h"

TowerDefense::Tower::Wizard::Wizard()
	:Tower(0.0f, 0.0f, 32, 32, 60.0f, 150, TowerType::DAMAGE, "res/textures/wizard.png", "res/textures/wizardHighlighted.png"),
	m_NumberOfMissiles(3)
{
	m_MagicDamage = 1.0f;
}

TowerDefense::Tower::Wizard::Wizard(float fireTime, int range, float damage, int numberOfMissiles)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::DAMAGE, "res/textures/wizard.png", "res/textures/wizardHighlighted.png"),
	m_NumberOfMissiles(numberOfMissiles)
{
	m_MagicDamage = damage;
}

void TowerDefense::Tower::Wizard::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	float damage = m_MagicDamage + m_MagicDamageModifier;
	if (Random::GetFloat() < m_CritChance)
	{
		damage *= m_CritMultiplier;
		Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 100, 100, "res/textures/critAnimation.png", 7, 30));
	}
	for (int i = 0; i < m_NumberOfMissiles; i++) {
		float angle = (i - ((m_NumberOfMissiles - 1) / 2.0f)) * (180.0f / m_NumberOfMissiles);
		Combat::AddEntity(std::make_shared<TowerDefense::MagicMissile>(m_X, m_Y, m_Rotation + angle, damage));
	}
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Tower::Wizard::GetRandomUpgrade(std::shared_ptr<std::vector<std::shared_ptr<Card>>> exclude)
{
	std::shared_ptr<Card> card;

	while (!card || ContainsCard(exclude, card)) {
		int randomCard = (int)(Random::GetFloat() * 4.0f);
		if (randomCard == 0)
			card = std::make_shared<AttackSpeedUpgrade>(.15f);
		else if (randomCard == 1)
			card = std::make_shared <DamageUpgrade>(1.0f, 1.0f);
		else if (randomCard == 2)
			card = std::make_shared <RangeUpgrade>(25);
		else if (randomCard == 3)
			card = std::make_shared <MoreMissiles>();
	}

	return card;
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Wizard::Clone()
{
	auto tower = std::make_shared<Wizard>(GetAttackTime(), GetRange(), m_MagicDamage, m_NumberOfMissiles);
	tower->SetDamageModifier(m_PhysicalDamageModifier, DamageType::PHYSICAL);
	tower->SetDamageModifier(m_MagicDamageModifier, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}