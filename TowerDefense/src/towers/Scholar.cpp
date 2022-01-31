#include "pch.h"
#include "Scholar.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "cards/SkillCards.h"
#include "core/Player.h"
#include "upgrades/Upgrade.h"
#include "scenes/Base.h"

TowerDefense::Tower::Scholar::Scholar(bool upgraded)
	:Tower(0.0f, 0.0f, 32, 32, 600.0f, 50, TowerType::SUPPORT, "Scholar"),
	m_Upgraded(upgraded), m_Focused(false), m_NumberOfFocus(1),
	m_FocusedImage(std::make_shared<Image>("ScholarSelected", 0.0f, 0.0f, m_Width, m_Height, 0.0f))
{}

void TowerDefense::Tower::Scholar::Update()
{
	Tower::Tower::Update();
	if (m_Focused)
		Entity::SetImage(m_FocusedImage);
}

void TowerDefense::Tower::Scholar::EndRound()
{
	m_Focused = true;
}

void TowerDefense::Tower::Scholar::Clicked()
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

void TowerDefense::Tower::Scholar::Fire(std::shared_ptr<TowerDefense::Entity> target)
{}

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Tower::Upgrade>>> TowerDefense::Tower::Scholar::GetPossibleUpgrades()
{
	auto upgrades = std::make_shared<std::vector<std::shared_ptr<Upgrade>>>();
	upgrades->push_back(std::make_shared<MoreFocus>());
	upgrades->push_back(std::make_shared<MoreFocus>());
	upgrades->push_back(std::make_shared<MoreFocus>());

	return upgrades;
}

bool TowerDefense::Tower::Scholar::CanUpgrade()
{
	return (GetLevel() < 4 || (GetLevel() < 9 && Base::ContainsScene("")));
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Scholar::Clone()
{
	auto tower = std::make_shared<Scholar>(m_Upgraded);
	tower->SetDamage(m_PhysicalDamage, DamageType::PHYSICAL);
	tower->SetDamage(m_MagicDamage, DamageType::MAGIC);
	tower->SetCritChance(m_CritChance);
	tower->SetCritMultiplier(m_CritMultiplier);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}