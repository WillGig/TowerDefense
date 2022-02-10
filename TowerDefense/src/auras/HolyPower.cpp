#include "pch.h"
#include "Aura.h"
#include "cards/TowerCard.h"
#include "towers/Paladin.h"
#include "towers/Cleric.h"

TowerDefense::Aura::HolyPower::HolyPower(float power)
	:Aura("HolyPower", "damageUp", "Paladins and Clerics\ngain " + Utils::TruncateFloat(power, 1) + " magic"),
	m_Power(power)
{}

void TowerDefense::Aura::HolyPower::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetCardType() == CardType::TOWER)
	{
		auto tower = std::dynamic_pointer_cast<TowerCard>(c)->GetHeldTower();

		auto paladin = std::dynamic_pointer_cast<Tower::Paladin>(tower);
		auto cleric = std::dynamic_pointer_cast<Tower::Cleric>(tower);

		if (paladin)
			paladin->SetDamage(paladin->GetDamage(Tower::DamageType::MAGIC) + m_Power, Tower::DamageType::MAGIC);
		if (cleric)
			cleric->SetDamage(cleric->GetDamage(Tower::DamageType::MAGIC) + m_Power, Tower::DamageType::MAGIC);
	}
}

void TowerDefense::Aura::HolyPower::Combine(std::shared_ptr<Aura> other)
{
	auto otherHolyPower = std::dynamic_pointer_cast<HolyPower>(other);
	if (otherHolyPower)
	{
		m_Power += otherHolyPower->GetPower();
		m_InfoText = std::make_unique<Text>("Paladins and Clerics\ngain " + Utils::TruncateFloat(m_Power, 1) + " magic", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

const std::string TowerDefense::Aura::HolyPower::GetSaveData() const
{
	return "Holy Power\n" + Utils::TruncateFloat(m_Power, 1);
}