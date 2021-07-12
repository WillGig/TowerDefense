#include "pch.h"
#include "Wizard.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "upgrades/Upgrade.h"
#include "scenes/Base.h"
#include "cards/LightningBolt.h"
#include "core/Board.h"
#include "GhostTower.h"

TowerDefense::Tower::Wizard::Wizard()
	:Tower(0.0f, 0.0f, 32, 32, 100.0f, 150, TowerType::DAMAGE, "Wizard"),
	m_NumberOfMissiles(3), m_Lightning(false), m_Summoner(false), m_GraveMissileFrequency(-1), m_GraveMissileTimer(0)
{
	m_MagicDamage = 1.0f;
	m_DamageType = DamageType::MAGIC;
}

TowerDefense::Tower::Wizard::Wizard(float fireTime, int range, float damage, int numberOfMissiles)
	: Tower(0.0f, 0.0f, 32, 32, fireTime, range, TowerType::DAMAGE, "Wizard"),
	m_NumberOfMissiles(numberOfMissiles), m_Lightning(false), m_Summoner(false), m_GraveMissileFrequency(-1), m_GraveMissileTimer(0)
{
	m_MagicDamage = damage;
	m_DamageType = DamageType::MAGIC;
}

void TowerDefense::Tower::Wizard::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
	if (m_Summoner)
	{
		Summon();
		return;
	}

	float damage = m_MagicDamage;
	if (Random::GetFloat() < m_CritChance)
	{
		damage *= m_CritMultiplier;
		Combat::AddEntity(std::make_shared<AnimationEffect>(m_X, m_Y, 32, 32, "critAnimation", 7, 30));
	}

	if (m_Lightning)
	{
		auto e = std::dynamic_pointer_cast<Enemy::Enemy>(target);
		auto targets = GetTargets(e);

		Vec2 prevTarget(m_X, m_Y);
		Vec2 currentTarget;
		for (unsigned int i = 0; i < targets.size(); i++)
		{
			targets[i]->TakeDamage(damage, GetID(), DamageType::MAGIC);
			currentTarget = Vec2(targets[i]->GetX(), targets[i]->GetY());
			//draw lightning connecting all targets
			Combat::AddEntity(std::make_shared<LightningBolt>(prevTarget, currentTarget));
			prevTarget = currentTarget;
		}
	}

	if (m_GraveMissileFrequency != -1)
	{
		if (m_GraveMissileTimer == 0)
		{
			for (int i = 0; i < m_NumberOfMissiles-2; i++) {
				float angle = (i - ((m_NumberOfMissiles - 3) / 2.0f)) * (180.0f / (m_NumberOfMissiles-2));
				Combat::AddEntity(std::make_shared<TowerDefense::GraveBolt>(m_X, m_Y, m_Rotation + angle, damage*1.5f, GetID()));
			}
			m_GraveMissileTimer = m_GraveMissileFrequency;
			return;
		}
		else
			m_GraveMissileTimer--;
	}

	for (int i = 0; i < m_NumberOfMissiles; i++) {
		float angle = (i - ((m_NumberOfMissiles - 1) / 2.0f)) * (180.0f / m_NumberOfMissiles);
		Combat::AddEntity(std::make_shared<TowerDefense::MagicMissile>(m_X, m_Y, m_Rotation + angle, damage, GetID()));
	}
}

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Tower::Upgrade>>> TowerDefense::Tower::Wizard::GetPossibleUpgrades()
{
	auto upgrades = std::make_shared<std::vector<std::shared_ptr<Upgrade>>>();

	if (GetLevel() < 4)
	{
		upgrades->push_back(std::make_shared<AttackSpeed>());
		upgrades->push_back(std::make_shared<Damage>());
		upgrades->push_back(std::make_shared<Range>());
		upgrades->push_back(std::make_shared<Crit>());
		upgrades->push_back(std::make_shared<MoreMissiles>());
	}
	else if(GetLevel() == 4)
	{
		upgrades->push_back(std::make_shared<WizardElementalist>());
		upgrades->push_back(std::make_shared<WizardConjurer>());
		upgrades->push_back(std::make_shared<WizardNecromancer>());
	}
	else
	{
		upgrades->push_back(std::make_shared<AttackSpeed>());
		upgrades->push_back(std::make_shared<Damage>());
		upgrades->push_back(std::make_shared<Range>());
		upgrades->push_back(std::make_shared<Crit>());
		upgrades->push_back(std::make_shared<MoreMissiles>());
	}

	return upgrades;
}

bool TowerDefense::Tower::Wizard::CanUpgrade()
{
	return (GetLevel() < 4 || (GetLevel() < 9 && Base::ContainsScene("WizardTower")));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Wizard::Clone()
{
	auto tower = std::make_shared<Wizard>(GetAttackTime(), GetRange(), m_MagicDamage, m_NumberOfMissiles);
	tower->SetDamage(m_PhysicalDamage, DamageType::PHYSICAL);
	tower->SetDamage(m_MagicDamage, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}

//Find all targets from lightning chaining between enemies in range of each other
std::vector<std::shared_ptr<TowerDefense::Enemy::Enemy>> TowerDefense::Tower::Wizard::GetTargets(std::shared_ptr<Enemy::Enemy> e)
{
	std::vector<std::shared_ptr<TowerDefense::Enemy::Enemy>> targets;

	targets.push_back(e);

	auto currentEnemy = e;
	while (auto enemy = GetEnemyInRange(currentEnemy, targets, 300.0f))
	{
		targets.push_back(enemy);
		currentEnemy = enemy;
	}

	return targets;
}

//Find the first enemy in range of the current target that is not already in the list
std::shared_ptr<TowerDefense::Enemy::Enemy> TowerDefense::Tower::Wizard::GetEnemyInRange(std::shared_ptr<Enemy::Enemy> currentEnemy, std::vector<std::shared_ptr<Enemy::Enemy>> exclude, float range)
{
	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++) {
		std::shared_ptr<Entity> e = entities->at(i);
		if (e->GetEntityType() == Type::ENEMY && e->GetID() != currentEnemy->GetID() && !Contains(exclude, e->GetID()))
		{
			float distance = e->GetDistance(m_X, m_Y);
			if (distance < range)
				return std::dynamic_pointer_cast<Enemy::Enemy>(e);
		}
	}

	return nullptr;
}

bool TowerDefense::Tower::Wizard::Contains(std::vector<std::shared_ptr<Enemy::Enemy>> list, unsigned int ID)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i]->GetID() == ID)
			return true;
	}
	return false;
}

//Summon random ghost tower in range of wizard
void TowerDefense::Tower::Wizard::Summon()
{
	auto tile = GetRandomTile();
	//TODO: Get random summon
	auto summon = GetRandomSummon();
	tile->SetContainedObject(summon);
	summon->SetX(tile->GetX());
	summon->SetY(tile->GetY());
	Combat::AddEntity(summon);
}

//Find random unoccupied tile within range of wizard tower
std::shared_ptr<TowerDefense::Tile> TowerDefense::Tower::Wizard::GetRandomTile()
{
	std::shared_ptr<Tile> tile;

	auto tiles = Board::Get().GetTiles();

	while (!tile)
	{
		float distance = Random::GetFloat() * GetRange()/2;
		float angle = Random::GetFloat() * PI * 2;

		float x = m_X + distance * cos(angle);
		float y = m_Y + distance * sin(angle);

		for (unsigned int i = 0; i < tiles->size(); i++)
		{
			if (tiles->at(i)->Contains(x, y))
			{
				auto t = tiles->at(i);
				if (!t->IsOccupied())
				{
					tile = t;
					SetRotation(angle * 360.0f / (PI * 2) - 90.0f);
				}
				break;
			}
		}
	}
	return tile;
}

//Return random ghost tower based on summon power level
std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Wizard::GetRandomSummon()
{
	return std::make_shared<GhostArcher>(m_MagicDamage, m_NumberOfMissiles - 2, m_CritChance, 180, GetID());
}