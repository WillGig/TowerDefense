#include "pch.h"
#include "Monk.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "cards/SkillCards.h"
#include "core/Player.h"
#include "upgrades/Upgrade.h"

TowerDefense::Tower::Monk::Monk(bool upgraded)
	:Tower(0.0f, 0.0f, 32, 32, 600.0f, 50, TowerType::SUPPORT, "Monk"),
	m_Upgraded(upgraded), m_Focused(false), m_NumberOfFocus(1),
	m_FocusedImage(std::make_shared<Image>("monkSelected", 0.0f, 0.0f, m_Width, m_Height, 0.0f))
{}

void TowerDefense::Tower::Monk::Update()
{
	Tower::Tower::Update();
	if (m_Focused)
		SetImage(m_FocusedImage);
}

void TowerDefense::Tower::Monk::EndRound()
{
	m_Focused = true;
}

void TowerDefense::Tower::Monk::Clicked()
{
	if (m_Focused) 
	{
		for (int i = 0; i < m_NumberOfFocus; i++)
		{
			std::shared_ptr<Focus> focusCard = std::make_shared<Focus>(true);
			if (m_Upgraded)
				focusCard->Upgrade();
			Player::Get().GetHand()->AddCard(focusCard);
		}
		m_Focused = false;
	}
	else
		Tower::Clicked();
}

void TowerDefense::Tower::Monk::Fire(std::shared_ptr<TowerDefense::Entity> target)
{}

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Tower::Upgrade>>> TowerDefense::Tower::Monk::GetPossibleUpgrades()
{
	auto upgrades = std::make_shared<std::vector<std::shared_ptr<Upgrade>>>();
	upgrades->push_back(std::make_shared<AttackSpeed>());
	upgrades->push_back(std::make_shared<Damage>());
	upgrades->push_back(std::make_shared<MoreFocus>());

	return upgrades;
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Monk::Clone()
{
	auto tower = std::make_shared<Monk>(m_Upgraded);
	tower->SetDamage(m_PhysicalDamage, DamageType::PHYSICAL);
	tower->SetDamage(m_MagicDamage, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}