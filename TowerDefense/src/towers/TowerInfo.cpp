#include "pch.h"
#include "TowerInfo.h"
#include "core/Player.h"
#include "scenes/Combat.h"
#include "towers/upgrades/Upgrade.h"

TowerDefense::TowerInfo::TowerInfo(float x, float y, std::shared_ptr<Tower::Tower> t)
	:Entity(x, y, 200, 180, 0.0f, "TowerInfo", Type::STATICIMAGE), m_Dragging(false), m_Upgrading(false),
	m_PreviousMouseX(0.0f), m_PreviousMouseY(0.0f), m_TowerDamage(t->GetDamage(t->GetDamageType())), 
	m_TowerAttackSpeed(t->GetAttackTime()), m_TowerRange(t->GetRange()), m_TowercritChance(t->GetCritChance()), 
	m_TowerDamageDealt(t->GetDamageDealt()), 
	m_Name(std::make_unique<Text>(t->GetName() , x, y + 74.0f, 14.0f, 200.0f)),
	m_Stats(std::make_unique<Text>("Damage Type:\nDamage:\nRange:\nAttack Speed:\nCrit Chance:\nTotal Damage:", m_X - 40.0f, m_Y - 8.0f, 10.0f, 200.0f)),
	m_EnergyIcon(std::make_unique<Image>("energyIcon", x + 80, y - 70, 20, 20, 0.0f)),
	m_TargetLeft(std::make_unique<Button>(x - 65, y + 52, 10, 20, "ArrowButton")),
	m_TargetRight(std::make_unique<Button>(x + 65, y + 52, 10, 20, "ArrowButton")),
	m_UpgradeButton(std::make_unique<Button>(x, y - 70, 66, 20, "upgradeButton")),
	m_Tower(t)
{
	m_TargetLeft->SetRotation(180.0f);

	UpdateTargetText();

	UpdateStatsText();
}

void TowerDefense::TowerInfo::Render()
{
	Entity::Render();
	m_Name->Render();
	m_Target->Render();
	m_Stats->Render();
	m_StatsNumbers->Render();
	m_Level->Render();
	m_UpgradeText->Render();
	m_TargetLeft->Render();
	m_TargetRight->Render();
	m_UpgradeButton->Render();
	m_EnergyIcon->Render();

	if (m_Upgrading)
	{
		auto upgrades = m_Tower->GetTowerUpgrades();
		for (unsigned int i = 0; i < upgrades->size(); i++)
			upgrades->at(i)->Render();
	}
}

void TowerDefense::TowerInfo::Update()
{
	if (m_TowerDamage != m_Tower->GetDamage(m_Tower->GetDamageType()) || m_TowerAttackSpeed != m_Tower->GetAttackTime() ||
		m_TowerRange != m_Tower->GetRange() || m_TowercritChance != m_Tower->GetCritChance() || 
		m_TowerDamageDealt != m_Tower->GetDamageDealt() || m_TowerLevel != m_Tower->GetLevel() || m_UpgradeCost != m_Tower->GetUpgradeCost())
		UpdateStatsText();

	if (Player::Get().GetHand()->DraggingCard() || Combat::DraggingEnemyInfo())
		return;

	m_TargetLeft->Update();
	m_TargetRight->Update();

	if (m_Upgrading)
	{
		auto upgrades = m_Tower->GetTowerUpgrades();
		for (unsigned int i = 0; i < upgrades->size(); i++)
		{
			upgrades->at(i)->Update();
			if (upgrades->at(i)->IsClicked())
			{
				upgrades->at(i)->UpgradeTower(m_Tower);
				upgrades->clear();
				m_Upgrading = false;
				break;
			}
		}
	}
	else
	{
		m_UpgradeButton->Update();

		Player& player = Player::Get();
		if (m_UpgradeButton->IsClicked() && player.GetEnergy() >= m_UpgradeCost)
		{
			m_Upgrading = true;
			player.ChangeEnergy(-m_UpgradeCost);
			auto upgrades = m_Tower->GetTowerUpgrades();
			for (int i = 0; i < (int)upgrades->size(); i++)
			{
				upgrades->at(i)->SetX(m_X + (1-i) * 70.0f);
				upgrades->at(i)->SetY(m_Y - 120.0f);
			}
		}
	}

	if (!Input::GetLeftMouseClicked())
		m_Dragging = false;

	if (m_Dragging)
	{
		float currentMouseX = Input::GetMouseX();
		float currentMouseY = Input::GetMouseY();

		SetX(m_X + currentMouseX - m_PreviousMouseX);
		SetY(m_Y + currentMouseY - m_PreviousMouseY);

		m_PreviousMouseX = currentMouseX;
		m_PreviousMouseY = currentMouseY;
	}
	else if (m_TargetLeft->IsClicked())
	{
		if((int)m_Tower->GetTargetType() == 0)
			m_Tower->SetTargetType((Tower::TargetType)(4));
		else
			m_Tower->SetTargetType((Tower::TargetType)(((int)m_Tower->GetTargetType() - 1)%5));
		UpdateTargetText();
	}
	else if (m_TargetRight->IsClicked())
	{
		m_Tower->SetTargetType((Tower::TargetType)(((int)m_Tower->GetTargetType() + 1) % 5));
		UpdateTargetText();
	}
	else if (Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetLeftMouseClicked())
	{
		m_Dragging = true;
		m_PreviousMouseX = Input::GetMouseX();
		m_PreviousMouseY = Input::GetMouseY();
	}
}

void TowerDefense::TowerInfo::SetX(float x)
{
	Entity::SetX(x);
	m_Name->SetPosition(m_X, m_Y + 74.0f, 0.0f);
	m_Target->SetPosition(m_X, m_Y + 54.0f, 0.0f);
	m_Stats->SetPosition(m_X - 40.0f, m_Y - 8.0f, 0.0f);
	m_StatsNumbers->SetPosition(m_X + 70.0f, m_Y - 8.0f, 0.0f);
	m_Level->SetPosition(m_X - 65.0f, m_Y - 70.0f, 0.0f);
	m_TargetLeft->SetX(x - 65);
	m_TargetRight->SetX(x + 65);
	m_UpgradeButton->SetX(x);
	m_UpgradeText->SetPosition(m_X + 52.0f, m_Y - 70.0f, 0.0f);
	m_EnergyIcon->SetPosition(m_X + 80, m_Y - 70, 0.0f);

	if (m_Upgrading)
	{
		auto upgrades = m_Tower->GetTowerUpgrades();
		for (int i = 0; i < (int)upgrades->size(); i++)
			upgrades->at(i)->SetX(m_X + (1 - i) * 70.0f);
	}
}

void TowerDefense::TowerInfo::SetY(float y)
{
	Entity::SetY(y);
	m_Name->SetPosition(m_X, m_Y + 74.0f, 0.0f);
	m_Target->SetPosition(m_X, m_Y + 54.0f, 0.0f);
	m_Stats->SetPosition(m_X - 40.0f, m_Y - 8.0f, 0.0f);
	m_StatsNumbers->SetPosition(m_X + 70.0f, m_Y - 8.0f, 0.0f);
	m_Level->SetPosition(m_X - 65.0f, m_Y - 70.0f, 0.0f);
	m_TargetLeft->SetY(y + 52);
	m_TargetRight->SetY(y + 52);
	m_UpgradeButton->SetY(y - 70);
	m_UpgradeText->SetPosition(m_X + 52.0f, m_Y - 70.0f, 0.0f);
	m_EnergyIcon->SetPosition(m_X + 80, m_Y - 70, 0.0f);

	if (m_Upgrading)
	{
		auto upgrades = m_Tower->GetTowerUpgrades();
		for (int i = 0; i < (int)upgrades->size(); i++)
			upgrades->at(i)->SetY(m_Y - 120.0f);
	}
}

void TowerDefense::TowerInfo::UpdateTargetText()
{
	std::string target = "Target - ";
	if (m_Tower->GetTargetType() == Tower::TargetType::FIRST)
		target += "First";
	else if (m_Tower->GetTargetType() == Tower::TargetType::LAST)
		target += "Last";
	else if (m_Tower->GetTargetType() == Tower::TargetType::CLOSE)
		target += "Close";
	else if (m_Tower->GetTargetType() == Tower::TargetType::STRONG)
		target += "Strong";
	else if (m_Tower->GetTargetType() == Tower::TargetType::WEAK)
		target += "Weak";

	m_Target = std::make_unique<Text>(target, m_X, m_Y + 54.0f, 10.0f, 200.0f);
}

void TowerDefense::TowerInfo::UpdateStatsText()
{
	m_TowerDamage = m_Tower->GetDamage(m_Tower->GetDamageType());
	m_TowerAttackSpeed = m_Tower->GetAttackTime();
	m_TowerRange = m_Tower->GetRange();
	m_TowercritChance = m_Tower->GetCritChance();
	m_TowerDamageDealt = m_Tower->GetDamageDealt();
	m_TowerLevel = m_Tower->GetLevel();
	m_UpgradeCost = m_Tower->GetUpgradeCost();

	std::string stats = "";
	if (m_Tower->GetDamageType() == Tower::DamageType::PHYSICAL)
		stats += "PHYS";
	else if (m_Tower->GetDamageType() == Tower::DamageType::MAGIC)
		stats += "MAGIC";

	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << m_TowerDamage;
	stats += "\n" + ss.str();

	stats += "\n";
	stats += std::to_string(m_TowerRange) + ".0";

	ss.str("");
	ss << std::fixed << std::setprecision(1) << (m_TowerAttackSpeed / 60.0f);
	stats += "\n" + ss.str() + "s";

	ss.str("");
	ss << std::fixed << std::setprecision(1) << (m_TowercritChance * 100.0f);
	stats += "\n" + ss.str() + "%";

	ss.str("");
	ss << std::fixed << std::setprecision(1) << (m_TowerDamageDealt);
	stats += "\n" + ss.str();

	m_StatsNumbers = std::make_unique<Text>(stats, m_X + 70.0f, m_Y - 8.0f, 10.0f, 200.0f);
	m_Level = std::make_unique<Text>("Lvl: " + std::to_string(m_TowerLevel), m_X - 65.0f, m_Y - 70.0f, 10.0f, 0.0f);
	m_UpgradeText = std::make_unique<Text>(std::to_string(m_UpgradeCost), m_X + 52.0f, m_Y - 70.0f, 10.0f, 0.0f);
}