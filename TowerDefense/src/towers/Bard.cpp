#include "pch.h"
#include "Bard.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "buffs/SpeedBuff.h"
#include "buffs/RangeBuff.h"
#include "buffs/CritDamageBuff.h"
#include "scenes/Base.h"
#include "upgrades/Upgrade.h"
#include "enemies/States/State.h"

TowerDefense::Tower::Bard::Bard()
	:Tower(0.0f, 0.0f, 32, 32, 60.0f, 75, TowerType::SUPPORT, "Bard"), 
	m_RangeBuff(0), m_SlowPercentage(0.0f), m_CritBuff(0.0f), m_HasAttack(false)
{
	m_MagicDamage = 1.0f;
	m_DamageType = DamageType::MAGIC;
}

TowerDefense::Tower::Bard::Bard(float fireTime, int range, float buff)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::SUPPORT, "Bard"),
	m_RangeBuff(0), m_SlowPercentage(0.0f), m_CritBuff(0.0f), m_HasAttack(false)
{
	m_MagicDamage = buff;
	m_DamageType = DamageType::MAGIC;
}

void TowerDefense::Tower::Bard::Update()
{
	Tower::Update();

	if (m_SlowPercentage == 0.0f)
		return;

	//Apply brief slow to enemies in range
	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++)
	{
		auto entity = entities->at(i);
		if (entity->GetEntityType() == Type::ENEMY)
		{
			if (GetDistance(entity->GetX(), entity->GetY()) < GetRange())
				std::dynamic_pointer_cast<Enemy::Enemy>(entity)->ApplyState(std::make_shared<Enemy::Slow>(Combat::GetRoundSpeed(), m_SlowPercentage));
		}
	}
}

void TowerDefense::Tower::Bard::Attack()
{
	Tower::Attack();
	if (m_HasAttack)
	{
		if (m_TowerType == TowerType::SUPPORT)
			m_TowerType = TowerType::DAMAGE;
		else
			m_TowerType = TowerType::SUPPORT;
	}
}

void TowerDefense::Tower::Bard::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	if (target->GetEntityType() == Type::TOWER)
	{
		std::shared_ptr<Tower> tower = std::dynamic_pointer_cast<Tower>(target);
		tower->ApplyBuff(std::make_shared<SpeedBuff>(150, m_ID, 1.0f + m_MagicDamage * 0.25f));
		if(m_RangeBuff > 0)
			tower->ApplyBuff(std::make_shared<RangeBuff>(150, m_ID, m_RangeBuff));
		if(m_CritBuff > 0.0f)
			tower->ApplyBuff(std::make_shared<CritDamageBuff>(150, m_ID, m_CritBuff));
	}
	else
	{
		std::shared_ptr<Enemy::Enemy> enemy = std::dynamic_pointer_cast<Enemy::Enemy>(target);
		if(enemy->GetDamage() > 1)
			enemy->SetDamage(enemy->GetDamage() - 1);
	}
}

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Tower::Upgrade>>> TowerDefense::Tower::Bard::GetPossibleUpgrades()
{
	auto upgrades = std::make_shared<std::vector<std::shared_ptr<Upgrade>>>();

	if (GetLevel() < 4)
	{
		upgrades->push_back(std::make_shared<AttackSpeed>());
		upgrades->push_back(std::make_shared<Damage>());
		upgrades->push_back(std::make_shared<Range>());
	}
	else if (GetLevel() == 4)
	{
		upgrades->push_back(std::make_shared<Pacifist>());
		upgrades->push_back(std::make_shared<Empowerer>());
		upgrades->push_back(std::make_shared<DisarmingWords>());
	}
	else
	{
		upgrades->push_back(std::make_shared<AttackSpeed>());
		upgrades->push_back(std::make_shared<Damage>());
		upgrades->push_back(std::make_shared<Range>());
	}

	return upgrades;
}

bool TowerDefense::Tower::Bard::CanUpgrade()
{
	return (GetLevel() < 4 || (GetLevel() < 9 && Base::ContainsScene("MusicHall")));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Bard::Clone()
{
	auto tower = std::make_shared<Bard>(GetAttackTime(), GetRange(), m_MagicDamage);
	tower->SetDamage(m_PhysicalDamage, DamageType::PHYSICAL);
	tower->SetDamage(m_MagicDamage, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}