#include "pch.h"
#include "Paladin.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"

TowerDefense::Tower::Paladin::Paladin()
	:Tower(0.0f, 0.0f, 32, 32, 120.0f, 50, TowerType::DAMAGE, "res/textures/paladin.png", "res/textures/paladinHighlighted.png")
{
	m_MagicDamage = .25f;
}

TowerDefense::Tower::Paladin::Paladin(float fireTime, int range, float damage)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::DAMAGE, "res/textures/paladin.png", "res/textures/paladinHighlighted.png")
{
	m_MagicDamage = damage;
}

void TowerDefense::Tower::Paladin::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	std::shared_ptr<Enemy::Enemy> e = std::dynamic_pointer_cast<Enemy::Enemy>(target);
	e->TakeDamage(e->GetMaxHealth() * m_MagicDamage);
	Combat::AddEntity(std::make_shared<AnimationEffect>(e->GetX(), e->GetY(), 100, 100, "res/textures/smiteAnimation.png", 7));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Paladin::Clone()
{
	auto tower = std::make_shared<Paladin>(GetAttackTime(), GetRange(), m_MagicDamage);
	tower->SetDamageModifier(m_PhysicalDamageModifier, DamageType::PHYSICAL);
	tower->SetDamageModifier(m_MagicDamageModifier, DamageType::MAGIC);
	return tower;
}