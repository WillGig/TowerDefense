#include "pch.h"
#include "TowerInfo.h"
#include "core/Player.h"
#include "scenes/Combat.h"

TowerDefense::TowerInfo::TowerInfo(float x, float y, std::shared_ptr<Tower::Tower> t)
	:Entity(x, y, 200, 155, 0.0f, "TowerInfo", Type::STATICIMAGE), m_Dragging(false),
	m_PreviousMouseX(0.0f), m_PreviousMouseY(0.0f), m_TowerDamage(t->GetDamage(t->GetDamageType())), 
	m_TowerAttackSpeed(t->GetAttackTime()), m_TowerRange(t->GetRange()), m_TowercritChance(t->GetCritChance()), 
	m_TowerDamageDealt(t->GetDamageDealt()), m_Name(std::make_unique<Text>(t->GetName() , x, y + 62.0f, 14.0f, 200.0f)),
	m_TargetLeft(std::make_unique<Button>(x - 65, y + 40, 10, 20, "ArrowButton")),
	m_TargetRight(std::make_unique<Button>(x + 65, y + 40, 10, 20, "ArrowButton")),
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
	m_TargetLeft->Render();
	m_TargetRight->Render();
}

void TowerDefense::TowerInfo::Update()
{
	if (m_TowerDamage != m_Tower->GetDamage(m_Tower->GetDamageType()) || m_TowerAttackSpeed != m_Tower->GetAttackTime() ||
		m_TowerRange != m_Tower->GetRange() || m_TowercritChance != m_Tower->GetCritChance() || m_TowerDamageDealt != m_Tower->GetDamageDealt())
		UpdateStatsText();

	if (Player::Get().GetHand()->DraggingCard() || Combat::DraggingEnemyInfo())
		return;

	m_TargetLeft->Update();
	m_TargetRight->Update();

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
	m_Name->SetPosition(m_X, m_Y + 62.0f, 0.0f);
	m_Target->SetPosition(m_X, m_Y + 42.0f, 0.0f);
	m_Stats->SetPosition(m_X, m_Y - 20.0f, 0.0f);
	m_TargetLeft->SetX(x - 65);
	m_TargetRight->SetX(x + 65);
}

void TowerDefense::TowerInfo::SetY(float y)
{
	Entity::SetY(y);
	m_Name->SetPosition(m_X, m_Y + 62.0f, 0.0f);
	m_Target->SetPosition(m_X, m_Y + 42.0f, 0.0f);
	m_Stats->SetPosition(m_X, m_Y - 20.0f, 0.0f);
	m_TargetLeft->SetY(y + 40);
	m_TargetRight->SetY(y + 40);
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

	m_Target = std::make_unique<Text>(target, m_X, m_Y + 42.0f, 10.0f, 200.0f);
}

void TowerDefense::TowerInfo::UpdateStatsText()
{
	m_TowerDamage = m_Tower->GetDamage(m_Tower->GetDamageType());
	m_TowerAttackSpeed = m_Tower->GetAttackTime();
	m_TowerRange = m_Tower->GetRange();
	m_TowercritChance = m_Tower->GetCritChance();
	m_TowerDamageDealt = m_Tower->GetDamageDealt();

	std::string stats = "Damage Type: ";
	if (m_Tower->GetDamageType() == Tower::DamageType::PHYSICAL)
		stats += "      PHYS";
	else if (m_Tower->GetDamageType() == Tower::DamageType::MAGIC)
		stats += "      MAGIC";

	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << m_TowerDamage;
	stats += "\nDamage:                  " + ss.str();

	stats += "\nRange:                 ";
	if (m_TowerRange < 100)
		stats += " ";
	stats += std::to_string(m_TowerRange) + ".0";

	ss.str("");
	ss << std::fixed << std::setprecision(1) << (m_TowerAttackSpeed / 60.0f);
	stats += "\nAttack Speed:          " + ss.str() + "s";

	ss.str("");
	ss << std::fixed << std::setprecision(1) << (m_TowercritChance * 100.0f);
	stats += "\nCrit Chance:            " + ss.str() + "%";

	ss.str("");
	ss << std::fixed << std::setprecision(1) << (m_TowerDamageDealt);
	stats += "\nTotal Damage:       ";
	if (m_TowerDamageDealt < 10)
		stats += " ";
	if (m_TowerDamageDealt < 100)
		stats += " ";
	if (m_TowerDamageDealt < 1000)	
		stats += " ";
	stats += ss.str();

	m_Stats = std::make_unique<Text>(stats, m_X, m_Y - 20.0f, 10.0f, 200.0f);
}