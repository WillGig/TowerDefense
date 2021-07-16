#include "pch.h"
#include "Paladin.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "scenes/Base.h"
#include "upgrades/Upgrade.h"
#include "buffs/SpeedBuff.h"

TowerDefense::Tower::Paladin::Paladin()
	:Tower(0.0f, 0.0f, 32, 32, 120.0f, 80, TowerType::DAMAGE, "Paladin"), m_CircleTimer(0), m_Inspiring(false),
	m_Speed(0.0f), m_XDisplacement(0.0f), m_YDisplacement(0.0f), m_DamageRadius(0.0f), m_DamageRadiusCircle(0.0f, 0.0f, 0.0f)
{
	m_MagicDamage = 5.0f;
	m_DamageType = DamageType::MAGIC;
}

TowerDefense::Tower::Paladin::Paladin(float fireTime, int range, float damage)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::DAMAGE, "Paladin"), m_CircleTimer(0), m_Inspiring(false),
	m_Speed(0.0f), m_XDisplacement(0.0f), m_YDisplacement(0.0f), m_DamageRadius(0.0f), m_DamageRadiusCircle(0.0f, 0.0f, 0.0f)
{
	m_MagicDamage = damage;
	m_DamageType = DamageType::MAGIC;
}

void TowerDefense::Tower::Paladin::Update()
{
	Tower::Update();
	if (m_Speed > 0.0f)
		for(int i = 0; i < Combat::GetRoundSpeed(); i++)
			Move();
	if (m_CircleTimer > 0)
		m_CircleTimer -= Combat::GetRoundSpeed();
}

void TowerDefense::Tower::Paladin::Render()
{
	Tower::Render();
	if (m_DamageRadius > 0.0f && m_CircleTimer > 0)
		m_DamageRadiusCircle.Render();
}

void TowerDefense::Tower::Paladin::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	float damage = m_MagicDamage;
	if (Random::GetFloat() < m_CritChance)
	{
		damage *= m_CritMultiplier;
		Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 32, 32, "critAnimation", 7, 30));

		if (m_Inspiring)
		{
			auto entities = Combat::GetEntities();
			for (unsigned int i = 0; i < entities->size(); i++) {
				auto e = entities->at(i);
				if (e->GetEntityType() == Type::TOWER)
				{
					if (GetDistance(e->GetX(), e->GetY()) < GetRange())
						std::dynamic_pointer_cast<Tower>(e)->ApplyBuff(std::make_shared<SpeedBuff>(120, GetID(), m_CritMultiplier));
				}
			}
		}
	}
	std::shared_ptr<Enemy::Enemy> e = std::dynamic_pointer_cast<Enemy::Enemy>(target);
	e->TakeDamage(e->GetMaxHealth() * damage * .01f + damage, GetID(), DamageType::MAGIC);
	Combat::AddEntity(std::make_shared<AnimationEffect>(e->GetX(), e->GetY(), 100, 100, "smiteAnimation", 7, 30));

	if (m_DamageRadius > 0.0f)
	{
		auto entities = Combat::GetEntities();
		for (unsigned int i = 0; i < entities->size(); i++) {
			auto entity = entities->at(i);
			if (entity->GetEntityType() == Type::ENEMY)
			{
				if (entity->GetID() != e->GetID() && entity->GetDistance(e->GetX(), e->GetY()) < m_DamageRadius)
					std::dynamic_pointer_cast<Enemy::Enemy>(entity)->TakeDamage(damage, GetID(), DamageType::MAGIC);
			}
		}

		m_CircleTimer = 30;
		m_DamageRadiusCircle = Circle(e->GetX(), e->GetY(), m_DamageRadius);
		m_DamageRadiusCircle.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
}

bool TowerDefense::Tower::Paladin::CanUpgrade()
{
	return (GetLevel() < 4 || (GetLevel() < 9 && Base::ContainsScene("Temple")));
}

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Tower::Upgrade>>> TowerDefense::Tower::Paladin::GetPossibleUpgrades()
{
	auto upgrades = std::make_shared<std::vector<std::shared_ptr<Upgrade>>>();

	if (GetLevel() < 4)
	{
		upgrades->push_back(std::make_shared<AttackSpeed>());
		upgrades->push_back(std::make_shared<Damage>());
		upgrades->push_back(std::make_shared<Range>());
		upgrades->push_back(std::make_shared<Crit>());
	}
	else if (GetLevel() == 4)
	{
		upgrades->push_back(std::make_shared<Wings>());
		upgrades->push_back(std::make_shared<Vengence>());
		upgrades->push_back(std::make_shared<InspiringLeader>());
	}
	else
	{
		upgrades->push_back(std::make_shared<AttackSpeed>());
		upgrades->push_back(std::make_shared<Damage>());
		upgrades->push_back(std::make_shared<Range>());
		upgrades->push_back(std::make_shared<Crit>());
	}

	return upgrades;
}

//Returns target enemy based on targetting priority
std::shared_ptr<TowerDefense::Entity>  TowerDefense::Tower::Paladin::FindTarget()
{
	if (m_Speed == 0.0f)
		return Tower::FindTarget();

	std::shared_ptr<Enemy::Enemy> targetEnemy;
	auto entities = Combat::GetEntities();
	auto targetType = GetTargetType();
	for (unsigned int i = 0; i < entities->size(); i++) {
		auto e = entities->at(i);
		if (e->GetEntityType() == Type::ENEMY) {
			auto enemy = std::dynamic_pointer_cast<Enemy::Enemy>(e);

			if (!enemy->Visible() && !m_SeeInvisibility)
				continue;

			if (!targetEnemy)
				targetEnemy = enemy;
			else if (targetType == TargetType::FIRST && enemy->GetDistanceTraveled() > targetEnemy->GetDistanceTraveled())
				targetEnemy = enemy;
			else if (targetType == TargetType::LAST && enemy->GetDistanceTraveled() < targetEnemy->GetDistanceTraveled())
				targetEnemy = enemy;
			else if (targetType == TargetType::CLOSE && GetDistance(e->GetX(), e->GetY()) < GetDistance(targetEnemy->GetX(), targetEnemy->GetY()))
				targetEnemy = enemy;
			else if (targetType == TargetType::STRONG && enemy->GetHealth() > targetEnemy->GetHealth())
				targetEnemy = enemy;
			else if (targetType == TargetType::WEAK && enemy->GetHealth() < targetEnemy->GetHealth())
				targetEnemy = enemy;
		}
	}
	return targetEnemy;
}

void TowerDefense::Tower::Paladin::Attack()
{
	if (m_Speed == 0)
	{
		Tower::Attack();
		return;
	}

	std::shared_ptr<TowerDefense::Entity> target = FindTarget();
	if (target) {
		if (GetDistance(target->GetX(), target->GetY()) < GetRange())
		{
			SetRotation(FindDirection(target->GetX(), target->GetY()));
			Fire(target);
			m_FireReady = 0;
		}
	}
}

void TowerDefense::Tower::Paladin::Move()
{
	std::shared_ptr<TowerDefense::Entity> target = FindTarget();
	if (target) {
		if (GetDistance(target->GetX(), target->GetY()) > GetRange())
		{
			//move towards target
			SetRotation(FindDirection(target->GetX(), target->GetY()));
			float xChange = -m_Speed * sin(m_Rotation * PI / 180.0f);
			float yChange =  m_Speed * cos(m_Rotation * PI / 180.0f);

			SetX(m_X + xChange);
			SetY(m_Y + yChange);
			m_XDisplacement += xChange;
			m_YDisplacement += yChange;
		}
	}
	else
	{
		//move towards home
		if (m_XDisplacement > m_Speed || m_YDisplacement > m_Speed)
		{
			SetRotation(FindDirection(m_X - m_XDisplacement, m_Y - m_YDisplacement));
			float xChange = -m_Speed * sin(m_Rotation * PI / 180.0f);
			float yChange = m_Speed * cos(m_Rotation * PI / 180.0f);
			SetX(m_X + xChange);
			SetY(m_Y + yChange);
			m_XDisplacement += xChange;
			m_YDisplacement += yChange;
		}
		else if (m_XDisplacement != 0 || m_YDisplacement != 0)
		{
			SetX(m_X - m_XDisplacement);
			SetY(m_Y - m_YDisplacement);
			m_XDisplacement = 0.0f;
			m_YDisplacement = 0.0f;
		}
	}
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