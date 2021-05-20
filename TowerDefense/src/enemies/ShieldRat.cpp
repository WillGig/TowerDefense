#include "pch.h"
#include "Enemies.h"

void TowerDefense::Enemy::ShieldRat::TakeDamage(float damage, unsigned int source, Tower::DamageType type)
{
	if (damage > 9)
		DropShield();
	Enemy::TakeDamage(damage, source, type);
}

void TowerDefense::Enemy::ShieldRat::DropShield()
{
	m_Armor = 0.0f;
	m_RegularImage = std::make_shared<Image>("ShieldlessRat", m_X, m_Y, m_Width, m_Height, m_Rotation);
	m_SelectedImage = std::make_shared<Image>("ShieldlessRatSelected", m_X, m_Y, m_Width, m_Height, m_Rotation);
}