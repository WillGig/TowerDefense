#include "pch.h"
#include "Aura.h"
#include "cards/TowerCard.h"
#include "towers/Archer.h"
#include "towers/Ranger.h"

TowerDefense::Aura::ArcherCritDamage::ArcherCritDamage(float damage)
	:Aura("ArcherCritDamage", "critDamage", "Archers and Rangers\ngain " + Utils::TruncateFloat(damage * 100, 1) + "% crit damage"),
	m_Damage(damage)
{}

void TowerDefense::Aura::ArcherCritDamage::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetCardType() == CardType::TOWER)
	{
		auto tower = std::dynamic_pointer_cast<TowerCard>(c)->GetHeldTower();

		auto archer = std::dynamic_pointer_cast<Tower::Archer>(tower);
		auto ranger = std::dynamic_pointer_cast<Tower::Ranger>(tower);

		if (archer)
			archer->SetCritMultiplier(archer->GetCritMultiplier() + m_Damage);
		else if (ranger)
			ranger->SetCritMultiplier(ranger->GetCritMultiplier() + m_Damage);
	}
}

void TowerDefense::Aura::ArcherCritDamage::Combine(std::shared_ptr<Aura> other)
{
	auto otherArcherDamage = std::dynamic_pointer_cast<ArcherCritDamage>(other);
	if (otherArcherDamage)
	{
		m_Damage += otherArcherDamage->GetDamage();
		m_InfoText = std::make_unique<Text>("Archers and Rangers\ngain " + Utils::TruncateFloat(m_Damage * 100, 1) + "% crit damage", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

const std::string TowerDefense::Aura::ArcherCritDamage::GetSaveData() const
{
	return "Archer Crit Damage\n" + Utils::TruncateFloat(m_Damage*100, 1);
}