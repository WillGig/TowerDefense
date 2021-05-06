#include "pch.h"
#include "CombatReward.h"
#include "core/Player.h"

TowerDefense::CombatReward::CombatReward(const std::string msg)
	:Button(0.0f, 0.0f, 180, 50, "CombatReward"),
	m_Text(std::make_unique<Text>(msg, 0.0f, 0.0f, 12.0f, 0.0f)), m_RewardTaken(false)
{
	m_Text->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::CombatReward::Render()
{
	Button::Render();
	m_Text->Render();
}

void TowerDefense::CombatReward::Update()
{
	Button::Update();
	if (IsClicked())
		OnClicked();
}

void TowerDefense::CombatReward::SetPosition(float x, float y)
{
	Button::SetX(x);
	Button::SetY(y);
	m_Text->SetPosition(x, y, 0.0f);
}

TowerDefense::GoldReward::GoldReward(int amount)
	:CombatReward(std::to_string(amount)), m_GoldAmount(amount),
	m_CoinImage(std::make_unique<Image>("goldIcon", 0.0f, 0.0f, 24, 24, 0.0f))
{
}

void TowerDefense::GoldReward::Render()
{
	CombatReward::Render();
	m_CoinImage->Render();
}

void TowerDefense::GoldReward::OnClicked()
{
	Player::Get().ChangeGold(m_GoldAmount);
	m_RewardTaken = true;
}

void TowerDefense::GoldReward::SetPosition(float x, float y)
{
	CombatReward::SetPosition(x, y);
	m_CoinImage->SetPosition(x + 30, y - 2.0f, 0.0f);
}