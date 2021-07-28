#include "pch.h"
#include "Cleric.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "buffs/DamageBuff.h"
#include "scenes/Base.h"
#include "core/Player.h"
#include "upgrades/Upgrade.h"

TowerDefense::Tower::Cleric::Cleric()
	:Tower(0.0f, 0.0f, 32, 32, 60.0f, 75, TowerType::SUPPORT, "Cleric"), m_Heal(0), m_ShredAuraPercent(0), m_HasAttack(false)
{
	m_MagicDamage = 1.0f;
	m_DamageType = DamageType::MAGIC;
}

TowerDefense::Tower::Cleric::Cleric(float fireTime, int range, float buff)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::SUPPORT, "Cleric"), m_Heal(0), m_ShredAuraPercent(0), m_HasAttack(false)
{
	m_MagicDamage = buff;
	m_DamageType = DamageType::MAGIC;
}

void TowerDefense::Tower::Cleric::Update()
{
	Tower::Update();

	if (m_ShredAuraPercent == 0.0f)
		return;

	//Reduce armor and magic resistance of all enemies in range
	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++)
	{
		auto entity = entities->at(i);
		if (entity->GetEntityType() == Type::ENEMY)
		{
			if (GetDistance(entity->GetX(), entity->GetY()) < GetRange())
			{}
				//TODO: Apply shred debuff
		}
	}
}

void TowerDefense::Tower::Cleric::Attack()
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

void TowerDefense::Tower::Cleric::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	if (target->GetEntityType() == Type::TOWER)
	{
		std::shared_ptr<Tower> tower = std::dynamic_pointer_cast<Tower>(target);
		tower->ApplyBuff(std::make_shared<DamageBuff>(150, m_ID, DamageType::MAGIC, m_MagicDamage));
		tower->ApplyBuff(std::make_shared<DamageBuff>(150, m_ID, DamageType::PHYSICAL, m_MagicDamage));
	}
	else
	{
		float damage = m_MagicDamage;
		if (Random::GetFloat() < m_CritChance)
		{
			damage *= m_CritMultiplier;
			Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 32, 32, "critAnimation", 7, 30));
		}

		std::shared_ptr<Enemy::Enemy> enemy = std::dynamic_pointer_cast<Enemy::Enemy>(target);
		enemy->TakeDamage(damage, GetID(), DamageType::MAGIC);
		Combat::AddEntity(std::make_shared<AnimationEffect>(enemy->GetX(), enemy->GetY(), 50, 50, "smiteAnimation", 7, 30));
	}
}

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Tower::Upgrade>>> TowerDefense::Tower::Cleric::GetPossibleUpgrades()
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
		upgrades->push_back(std::make_shared<Lifebringer>());
		upgrades->push_back(std::make_shared<BattleCleric>());
		upgrades->push_back(std::make_shared<DeathPriest>());
	}
	else
	{
		upgrades->push_back(std::make_shared<AttackSpeed>());
		upgrades->push_back(std::make_shared<Damage>());
		upgrades->push_back(std::make_shared<Range>());
	}

	return upgrades;
}

bool TowerDefense::Tower::Cleric::CanUpgrade()
{
	return (GetLevel() < 4 || (GetLevel() < 9 && Base::ContainsScene("Temple")));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Cleric::Clone()
{
	auto tower = std::make_shared<Cleric>(GetAttackTime(), GetRange(), m_MagicDamage);
	tower->SetDamage(m_PhysicalDamage, DamageType::PHYSICAL);
	tower->SetDamage(m_MagicDamage, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}

void TowerDefense::Tower::Cleric::EndRound()
{
	if (m_Heal > 0)
		Player::Get().ChangeHealth(m_Heal);
}