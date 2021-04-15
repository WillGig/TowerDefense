#include "pch.h"
#include "Monk.h"
#include "scenes/Combat.h"
#include "projectiles/Projectiles.h"
#include "cards/Focus.h"
#include "core/Player.h"

TowerDefense::Tower::Monk::Monk(bool upgraded)
	:Tower(0.0f, 0.0f, 32, 32, 600.0f, 50, TowerType::SUPPORT, "res/textures/monk.png", "res/textures/monkHighlighted.png"),
	m_Upgraded(upgraded), m_Focused(false), m_FocusedImage(std::make_shared<Image>("res/textures/monkSelected.png", 0.0f, 0.0f, m_Width, m_Height, 0.0f))
{
}

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
		std::shared_ptr<Focus> focusCard = std::make_shared<Focus>(true);
		if (m_Upgraded)
			focusCard->Upgrade();
		Player::Get().GetHand()->AddCard(focusCard);
		m_Focused = false;
	}
	Tower::Clicked();
}

void TowerDefense::Tower::Monk::Fire(std::shared_ptr<TowerDefense::Entity> target)
{
}

std::shared_ptr<TowerDefense::Tower::Tower> TowerDefense::Tower::Monk::Clone()
{
	auto tower = std::make_shared<Monk>(m_Upgraded);
	tower->SetDamageModifier(m_PhysicalDamageModifier, DamageType::PHYSICAL);
	tower->SetDamageModifier(m_MagicDamageModifier, DamageType::MAGIC);
	tower->SetWidth(m_Width);
	tower->SetHeight(m_Height);
	return tower;
}