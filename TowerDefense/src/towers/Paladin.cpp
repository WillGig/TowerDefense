#include "pch.h"
#include "Paladin.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"

TowerDefense::Tower::Paladin::Paladin()
	:Tower(0.0f, 0.0f, 32, 32, 100.0f, 75, TowerType::DAMAGE, "Paladin")
{
	m_MagicDamage = 3.0f;
	m_DamageType = DamageType::MAGIC;
}

TowerDefense::Tower::Paladin::Paladin(float fireTime, int range, float damage)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::DAMAGE, "Paladin")
{
	m_MagicDamage = damage;
	m_DamageType = DamageType::MAGIC;
}

void TowerDefense::Tower::Paladin::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	float damage = m_MagicDamage;
	if (Random::GetFloat() < m_CritChance)
	{
		damage *= m_CritMultiplier;
		Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 32, 32, "critAnimation", 7, 30));
	}
	std::shared_ptr<Enemy::Enemy> e = std::dynamic_pointer_cast<Enemy::Enemy>(target);
	e->TakeDamage(e->GetMaxHealth() * damage * .01f + damage, GetID());
	Combat::AddEntity(std::make_shared<AnimationEffect>(e->GetX(), e->GetY(), 100, 100, "smiteAnimation", 7, 30));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Paladin::Clone()
{
	auto tower = std::make_shared<Paladin>(GetAttackTime(), GetRange(), m_MagicDamage);
	tower->SetDamage(m_PhysicalDamage, DamageType::PHYSICAL);
	tower->SetDamage(m_MagicDamage, DamageType::MAGIC);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}