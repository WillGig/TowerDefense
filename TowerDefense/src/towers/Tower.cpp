#include "pch.h"
#include "Tower.h"
#include "core/Clock.h"
#include "TowerDefense.h"
#include "scenes/Combat.h"
#include "core/Board.h"
#include "enemies/Enemy.h"
#include "core/Player.h"
#include "towers/upgrades/Upgrade.h"
#include "cards/upgrades/Upgrades.h"

TowerDefense::Tower::Tower::Tower(float x, float y, int width, int height, float fireTime, int range, TowerType type, const std::string& name)
	:Entity(x, y, width, height, 0.0f, name, Type::TOWER),
	m_DamageType(), m_PhysicalDamage(0.0f), m_MagicDamage(0.0f), 
	m_Spread(0.0f), m_CritChance(0.0f), m_CritMultiplier(2.0f), 
	m_ArmorPenChance(0.0f), m_ArmorPenReduction(.5f), m_SeeInvisibility(false),
	m_FireTime(fireTime), m_TotalDamageDealt(0), m_Level(1), m_FireReady(1000), m_Range(range), m_Highlighted(false), m_Clicked(false), 
	m_TowerType(type), m_Name(name), m_TargetType(TargetType::FIRST), 
	m_RegularImage(std::make_shared<Image>(name, x, y, width, height, 0.0f)),
	m_HighlightedImage(std::make_shared<Image>(name + "Highlighted", x, y, width, height, 0.0f)),
	m_RangeCircle(std::make_shared<Circle>(0.0f, 0.0f, (float)range)),
	m_Buffs(std::make_unique<std::vector<std::shared_ptr<Buff>>>()), 
	m_AddBuffs(std::make_unique<std::vector<std::shared_ptr<Buff>>>()), 
	m_RemoveBuffs(std::make_unique<std::vector<unsigned int>>()),
	m_Upgrades(std::make_shared<std::vector<std::shared_ptr<Upgrade>>>())
{
	m_RangeCircle->SetColor(0.0f, 1.0f, 0.0f, 1.0f);
}

void TowerDefense::Tower::Tower::Update()
{
	UpdateImage();

	m_Clicked = false;
	bool cardSelected = Player::Get().GetHand()->GetSelectedCard() != -1;

	if (Contains(Input::GetMouseX(), Input::GetMouseY()) && !cardSelected && !Combat::DraggingInfo() && Input::GetLeftMouseClickedAndSetFalse())
		Clicked();

	if (Combat::Paused())
		return;

	for (int i = 0; i < Combat::GetRoundSpeed(); i++)
	{
		if (m_FireReady >= m_FireTime)
			Attack();
		else
			m_FireReady ++;
	}

	UpdateBuffs();
}

void TowerDefense::Tower::Tower::UpdateImage()
{
	if (m_Highlighted)
	{
		Entity::SetImage(m_HighlightedImage);
		m_Highlighted = false;
	}
	else
		Entity::SetImage(m_RegularImage);
}

void TowerDefense::Tower::Tower::Attack()
{
	std::shared_ptr<TowerDefense::Entity> target = FindTarget();
	if (target) {
		SetRotation(FindDirection(target->GetX(), target->GetY()));
		Fire(target);
		m_FireReady = 0;
	}
}

void TowerDefense::Tower::Tower::UpdateBuffs()
{
	//Update Buffs
	for (unsigned int i = 0; i < m_Buffs->size(); i++)
		m_Buffs->at(i)->Update(*this);

	//Add all Buffs from AddBuffs and clear
	for (unsigned int i = 0; i < m_AddBuffs->size(); i++)
		m_Buffs->push_back(m_AddBuffs->at(i));
	m_AddBuffs->clear();

	//Remove all Buffs from RemoveBuffs and clear
	for (unsigned int i = 0; i < m_RemoveBuffs->size(); i++)
	{
		for (unsigned int j = 0; j < m_Buffs->size(); j++)
		{
			if (m_RemoveBuffs->at(i) == m_Buffs->at(j)->GetID())
			{
				m_Buffs->erase(m_Buffs->begin() + j);
				break;
			}
		}
	}
	m_RemoveBuffs->clear();
}

void TowerDefense::Tower::Tower::SetX(float x)
{
	Entity::SetX(x);
	m_RangeCircle->SetPosition(m_X, m_Y, 1.0f);
}

void TowerDefense::Tower::Tower::SetY(float y)
{
	Entity::SetY(y);
	m_RangeCircle->SetPosition(m_X, m_Y, 1.0f);
}

void TowerDefense::Tower::Tower::SetImage(const std::string& image)
{
	m_RegularImage = std::make_shared<Image>(image, m_X, m_Y, m_Width, m_Height, m_Rotation);
	m_HighlightedImage = std::make_shared<Image>(image + "Highlighted", m_X, m_Y, m_Width, m_Height, m_Rotation);
}

int TowerDefense::Tower::Tower::GetUpgradeCost() const
{
	if (m_Level < 4)
		return 50;
	else if (m_Level < 9)
		return 100;
	return 200;
}

void TowerDefense::Tower::Tower::SetRange(int range)
{ 
	m_Range = range;  
	m_RangeCircle = std::make_shared<Circle>(0.0f, 0.0f, (float)range); 
	m_RangeCircle->SetColor(0.0f, 1.0f, 0.0f, 1.0f); 
	m_RangeCircle->SetPosition(m_X, m_Y, 1.0f);
}


//Returns 3 random upgrades to choose from for hero towers
/*std::shared_ptr<TowerDefense::CardChoice> TowerDefense::Tower::Tower::GetUpgrades()
{
	auto upgrades = std::make_shared<std::vector<std::shared_ptr<Card>>>();

	for (int i = 0; i < 3; i++)
		upgrades->push_back(GetRandomUpgrade(upgrades));

	return std::make_shared<CardChoice>(upgrades, -1);
}*/

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Tower::Upgrade>>> TowerDefense::Tower::Tower::GetTowerUpgrades()
{
	if (m_Upgrades->size() == 0)
	{
		auto upgrades = GetPossibleUpgrades();
		for (int i = 0; i < 3; i++)
		{
			int randomUpgrade = (int)(Random::GetFloat() * upgrades->size());
			m_Upgrades->push_back(upgrades->at(randomUpgrade));
			upgrades->erase(upgrades->begin() + randomUpgrade);
		}
	}
	return m_Upgrades;
}

//Generates random upgrade, excluding already chosen types of upgrades
//Can be overwritten in specific tower classes to customize buffs to specific towers
/*std::shared_ptr<TowerDefense::Card> TowerDefense::Tower::Tower::GetRandomUpgrade(std::shared_ptr<std::vector<std::shared_ptr<Card>>> exclude)
{
	std::shared_ptr<Card> card;

	while (!card || ContainsCard(exclude, card)) {
		int randomCard = (int)(Random::GetFloat() * 3.0f);
		if (randomCard == 0)
			card = std::make_shared<AttackSpeedUpgrade>(.20f);
		else if (randomCard == 1)
			card = std::make_shared <DamageUpgrade>(1.0f, 1.0f);
		else if (randomCard == 2)
			card = std::make_shared <RangeUpgrade>(25);
	}

	return card;
}*/

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Tower::Upgrade>>> TowerDefense::Tower::Tower::GetPossibleUpgrades()
{
	auto upgrades = std::make_shared<std::vector<std::shared_ptr<Upgrade>>>();
	upgrades->push_back(std::make_shared<AttackSpeed>());
	upgrades->push_back(std::make_shared<Damage>());
	upgrades->push_back(std::make_shared<Range>());
	upgrades->push_back(std::make_shared<Crit>());
	
	if (!CanSeeInvisibility())
		upgrades->push_back(std::make_shared<HeightenedSenses>());

	return upgrades;
}

//Helper function to check if the upgrades list already contains the randomly chosen upgrade
bool TowerDefense::Tower::Tower::ContainsCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>> exclude, std::shared_ptr<Card> card)
{
	for (unsigned int i = 0; i < exclude->size(); i++)
	{
		if (exclude->at(i)->GetName() == card->GetName())
			return true;
	}
	return false;
}

bool TowerDefense::Tower::Tower::ContainsUpgrade(std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> exclude, std::shared_ptr<Upgrade> upgrade)
{
	for (unsigned int i = 0; i < exclude->size(); i++)
	{
		if (exclude->at(i)->GetName() == upgrade->GetName())
			return true;
	}
	return false;
}

void TowerDefense::Tower::Tower::Clicked()
{
	m_Clicked = true;
}

//Removes tower from combat entities list and removes it from any contiaining tiles in the board
//Towers should never be removed from the list without calling this function
void TowerDefense::Tower::Tower::Destroy()
{
	Combat::RemoveEntity(m_ID);

	//Remove from any tiles it was contained in
	auto tiles = TowerDefense::Board::Get().GetTiles();
	for (unsigned int i = 0; i < tiles->size(); i++) {
		if (tiles->at(i)->GetContainedObject().get() == this) {
			tiles->at(i)->SetContainedObject(nullptr);
		}
	}
}

float TowerDefense::Tower::Tower::FindDirection(float x, float y)
{
	return atan2(y - m_Y, x - m_X)*180/PI - 90;
}

//Returns target enemy based on targetting priority
std::shared_ptr<TowerDefense::Entity>  TowerDefense::Tower::Tower::FindTarget()
{
	std::shared_ptr<Enemy::Enemy> targetEnemy;
	std::shared_ptr<Tower> targetTower;
	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++) {
		auto e = entities->at(i);
		if (GetDistance(e->GetX(), e->GetY()) > m_Range)
			continue;

		if (m_TowerType == TowerType::DAMAGE) {
			if (e->GetEntityType() == Type::ENEMY) {
				auto enemy = std::dynamic_pointer_cast<Enemy::Enemy>(e);

				if (!enemy->Visible() && !m_SeeInvisibility)
					continue;

				if (!targetEnemy)
					targetEnemy = enemy;
				else if (m_TargetType == TargetType::FIRST && enemy->GetDistanceTraveled() > targetEnemy->GetDistanceTraveled())
					targetEnemy = enemy;
				else if (m_TargetType == TargetType::LAST && enemy->GetDistanceTraveled() < targetEnemy->GetDistanceTraveled())
					targetEnemy = enemy;
				else if (m_TargetType == TargetType::CLOSE && GetDistance(e->GetX(), e->GetY()) < GetDistance(targetEnemy->GetX(), targetEnemy->GetY()))
					targetEnemy = enemy;
				else if (m_TargetType == TargetType::STRONG && enemy->GetHealth() > targetEnemy->GetHealth())
					targetEnemy = enemy;
				else if (m_TargetType == TargetType::WEAK && enemy->GetHealth() < targetEnemy->GetHealth())
					targetEnemy = enemy;
			}
		}
		else if (m_TowerType == TowerType::SUPPORT) {
			if (std::shared_ptr<Tower> tower = std::dynamic_pointer_cast<Tower>(e)) {
				if (tower->GetType() != TowerType::DAMAGE)
					continue;

				if (tower->IsBuffedBy(*this))
					continue;

				if (!targetTower || GetDistance(tower->GetX(), tower->GetY()) < GetDistance(targetTower->GetX(), targetTower->GetY())) {
					targetTower = tower;
				}
			}
		}
	}

	if (m_TowerType == TowerType::DAMAGE)
		return targetEnemy;
	else if(m_TowerType == TowerType::SUPPORT)
		return targetTower;

	return nullptr;
}

void TowerDefense::Tower::Tower::ApplyBuff(std::shared_ptr<Buff> buff)
{
	m_AddBuffs->push_back(buff);
	buff->Apply(*this);
}

void TowerDefense::Tower::Tower::RemoveBuff(int buffID)
{
	m_RemoveBuffs->push_back(buffID);
}

void TowerDefense::Tower::Tower::ClearBuffs()
{
	for (unsigned int i = 0; i < m_Buffs->size(); i++)
		m_Buffs->at(i)->Remove(*this);
}

//Used to ensure that the same tower or towers of the same type cannot stack buffs on one target
bool TowerDefense::Tower::Tower::IsBuffedBy(Tower& t)
{
	for (unsigned int i = 0; i < m_Buffs->size(); i++)
	{
		if (m_Buffs->at(i)->GetSource() == t.GetID())
			return true;
		if (std::dynamic_pointer_cast<Tower>(Combat::GetEntity(m_Buffs->at(i)->GetSource()))->GetName() == t.GetName())
			return true;
	}
	
	for (unsigned int i = 0; i < m_AddBuffs->size(); i++)
	{
		if (m_AddBuffs->at(i)->GetSource() == t.GetID())
			return true;
		if (std::dynamic_pointer_cast<Tower>(Combat::GetEntity(m_AddBuffs->at(i)->GetSource()))->GetName() == t.GetName())
			return true;
	}
	return false;
}