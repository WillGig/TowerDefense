#include "pch.h"
#include "EnemyInfo.h"
#include "core/Player.h"
#include "scenes/Combat.h"

TowerDefense::EnemyInfo::EnemyInfo(float x, float y, std::shared_ptr<Enemy::Enemy> e)
	:Entity(x, y, 150, 100, 0.0f, "EnemyInfo", Type::STATICIMAGE), m_Dragging(false),
	m_PreviousMouseX(0.0f), m_PreviousMouseY(0.0f), m_EnemyHP(e->GetHealth()), m_EnemySpeed(e->GetSpeed()),
	m_Name(std::make_unique<Text>(e->GetName(), x, y + 30.0f, 14.0f, 115.0f)), m_Enemy(e)
{
	if (e->GetName().size() > 8)
		m_Name = std::make_unique<Text>(e->GetName(), x, y + 30.0f, 10.0f, 115.0f);
	UpdateStatsText();
}

void TowerDefense::EnemyInfo::Render()
{
	Entity::Render();
	m_Name->Render();
	m_Stats->Render();
}

void TowerDefense::EnemyInfo::Update()
{
	if (m_EnemyHP != m_Enemy->GetHealth() || m_EnemySpeed != m_Enemy->GetSpeed() 
		|| m_EnemyArmor != m_Enemy->GetArmor() || m_EnemyMagicResistance != m_Enemy->GetMagicResistance())
		UpdateStatsText();

	if (Player::Get().GetHand()->DraggingCard() || Combat::DraggingTowerInfo())
		return;

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
	else if (Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetLeftMouseClicked())
	{
		m_Dragging = true;
		m_PreviousMouseX = Input::GetMouseX();
		m_PreviousMouseY = Input::GetMouseY();
	}
}

void TowerDefense::EnemyInfo::SetX(float x)
{
	Entity::SetX(x);
	m_Name->SetPosition(m_X, m_Y + 30.0f, 0.0f);
	m_Stats->SetPosition(m_X, m_Y - 10, 0.0f);
}

void TowerDefense::EnemyInfo::SetY(float y)
{
	Entity::SetY(y);
	m_Name->SetPosition(m_X, m_Y + 30.0f, 0.0f);
	m_Stats->SetPosition(m_X, m_Y - 10, 0.0f);
}

void TowerDefense::EnemyInfo::UpdateStatsText()
{
	m_EnemyHP = m_Enemy->GetHealth();
	m_EnemySpeed = m_Enemy->GetSpeed();
	m_EnemyArmor = m_Enemy->GetArmor();
	m_EnemyMagicResistance = m_Enemy->GetMagicResistance();

	std::string stats = "HP:                    ";

	if (m_EnemyHP < 10)
		stats += " ";
	if (m_EnemyHP < 100)
		stats += " ";
	if (m_EnemyHP < 1000)
		stats += " ";

	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << m_EnemyHP;
	stats += ss.str();

	stats += "\nSpeed:                 ";
	if (m_EnemySpeed*32.0f < 10)
		stats += " ";

	ss.str("");
	ss << std::fixed << std::setprecision(1) << (m_EnemySpeed * 32.0f);
	stats += ss.str();

	stats += "\nArmor:                 ";
	if (m_EnemySpeed * 32.0f < 10)
		stats += " ";

	ss.str("");
	ss << std::fixed << std::setprecision(1) << m_EnemyArmor;
	stats += ss.str();

	stats += "\nMagic Resistance: ";
	if (m_EnemySpeed * 32.0f < 10)
		stats += " ";

	ss.str("");
	ss << std::fixed << std::setprecision(1) << m_EnemyMagicResistance;
	stats += ss.str();

	m_Stats = std::make_unique<Text>(stats, m_X, m_Y - 10, 8.0f, 200.0f);
}