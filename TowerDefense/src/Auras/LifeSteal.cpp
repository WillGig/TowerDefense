#include "pch.h"
#include "Aura.h"
#include "core/Player.h"

TowerDefense::Aura::LifeSteal::LifeSteal(int steal)
	:Aura("LifeSteal", "lifeSteal", "Heal " + std::to_string(steal) + " health for\nevery enemy killed"), m_LifeSteal(steal)
{
}

void TowerDefense::Aura::LifeSteal::OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e)
{
	Player::Get().ChangeHealth(m_LifeSteal);
}

void TowerDefense::Aura::LifeSteal::Combine(std::shared_ptr<Aura> other)
{
	auto otherLifeSteal = std::dynamic_pointer_cast<LifeSteal>(other);
	if (otherLifeSteal)
	{
		m_LifeSteal += otherLifeSteal->GetLifeSteal();
		m_InfoText = std::make_unique<Text>("Heal " + std::to_string(m_LifeSteal) + " health for\nevery enemy killed", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

const std::string TowerDefense::Aura::LifeSteal::GetSaveData() const
{
	return "Life Steal\n" + std::to_string(m_LifeSteal);
}