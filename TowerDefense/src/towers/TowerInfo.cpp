#include "pch.h"
#include "TowerInfo.h"
#include "core/Player.h"

TowerDefense::TowerInfo::TowerInfo(float x, float y, std::shared_ptr<Tower::Tower> t)
	:Entity(200, 140, x, y, 0.0f, "TowerInfo", Type::STATICIMAGE), m_Dragging(false),
	m_PreviousMouseX(0.0f), m_PreviousMouseY(0.0f),
	m_Name(std::make_unique<Text>(t->GetName() , x, y + 52.0f, 14.0f, 200.0f))
{
	std::string target = "Target - ";
	if (t->GetTargetType() == Tower::TargetType::FIRST)
		target += "First";
	else if (t->GetTargetType() == Tower::TargetType::LAST)
		target += "Last";
	else if (t->GetTargetType() == Tower::TargetType::CLOSE)
		target += "Close";
	else if (t->GetTargetType() == Tower::TargetType::STRONG)
		target += "Strong";
	else if (t->GetTargetType() == Tower::TargetType::WEAK)
		target += "Weak";

	m_Target = std::make_unique<Text>(target, x, y + 32.0f, 10.0f, 200.0f);

	std::string stats = "Damage Type: ";
	if (t->GetDamageType() == Tower::DamageType::PHYSICAL)
		stats += "      PHYS";
	else if (t->GetDamageType() == Tower::DamageType::MAGIC)
		stats += "      MAGIC";

	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << t->GetDamage(t->GetDamageType());
	stats += "\nDamage:                  " + ss.str();

	stats += "\nRange:                 ";
	if (t->GetRange() < 100)
		stats += " ";
	stats += std::to_string(t->GetRange()) + ".0";

	ss.str("");
	ss << std::fixed << std::setprecision(1) << (t->GetAttackTime() / 60.0f);
	stats += "\nAttack Speed:          " + ss.str() + "s";

	ss.str("");
	ss << std::fixed << std::setprecision(1) << (t->GetCritChance()*100.0f);
	stats += "\nCrit Chance:            " + ss.str() + "%";

	m_Stats = std::make_unique<Text>(stats, x, y + 14.0f, 10.0f, 200.0f);
}

void TowerDefense::TowerInfo::Render()
{
	Entity::Render();
	m_Name->Render();
	m_Target->Render();
	m_Stats->Render();
}

void TowerDefense::TowerInfo::Update()
{
	if (Player::Get().GetHand()->DraggingCard())
		return;

	if (!Input::GetLeftMouseClicked())
	{
		m_Dragging = false;
		return;
	}
		
	if (m_Dragging)
	{
		float currentMouseX = Input::GetMouseX();
		float currentMouseY = Input::GetMouseY();

		SetX(m_X + currentMouseX - m_PreviousMouseX);
		SetY(m_Y + currentMouseY - m_PreviousMouseY);

		m_PreviousMouseX = currentMouseX;
		m_PreviousMouseY = currentMouseY;
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
	m_Name->SetPosition(m_X, m_Y + 52.0f, 0.0f);
	m_Target->SetPosition(m_X, m_Y + 32.0f, 0.0f);
	m_Stats->SetPosition(m_X, m_Y + 14.0f, 0.0f);
}

void TowerDefense::TowerInfo::SetY(float y)
{
	Entity::SetY(y);
	m_Name->SetPosition(m_X, m_Y + 52.0f, 0.0f);
	m_Target->SetPosition(m_X, m_Y + 32.0f, 0.0f);
	m_Stats->SetPosition(m_X, m_Y + 14.0f, 0.0f);
}