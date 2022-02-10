#include "pch.h"
#include "Aura.h"
#include "cards/TowerCard.h"
#include "towers/Bard.h"

TowerDefense::Aura::MusicPower::MusicPower(float power)
	:Aura("MusicPower", "damageUp", "Bards gain " + Utils::TruncateFloat(power, 1) + " magic"),
	m_Power(power)
{}

void TowerDefense::Aura::MusicPower::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetCardType() == CardType::TOWER)
	{
		auto tower = std::dynamic_pointer_cast<TowerCard>(c)->GetHeldTower();

		auto bard = std::dynamic_pointer_cast<Tower::Bard>(tower);

		if (bard)
			bard->SetDamage(bard->GetDamage(Tower::DamageType::MAGIC) + m_Power, Tower::DamageType::MAGIC);
	}
}

void TowerDefense::Aura::MusicPower::Combine(std::shared_ptr<Aura> other)
{
	auto otherMusicPower = std::dynamic_pointer_cast<MusicPower>(other);
	if (otherMusicPower)
	{
		m_Power += otherMusicPower->GetPower();
		m_InfoText = std::make_unique<Text>("Bards gain " + Utils::TruncateFloat(m_Power, 1) + " magic", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

const std::string TowerDefense::Aura::MusicPower::GetSaveData() const
{
	return "Music Power\n" + Utils::TruncateFloat(m_Power, 1);
}