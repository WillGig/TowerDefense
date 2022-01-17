#include "pch.h"
#include "Aura.h"
#include "cards/TowerCard.h"
#include "towers/Archer.h"

TowerDefense::Aura::MultiShot::MultiShot(int extraShots)
	:Aura("multiShot", "Archers gain + " + std::to_string(extraShots) + " Multishot"),
	m_ExtraShots(extraShots)
{}

void TowerDefense::Aura::MultiShot::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetCardType() == CardType::TOWER)
	{
		auto tower = std::dynamic_pointer_cast<TowerCard>(c)->GetHeldTower();
		auto archer = std::dynamic_pointer_cast<Tower::Archer>(tower);

		if (archer)
			archer->SetNumberOfArrows(archer->GetNumberOfArrows() + m_ExtraShots);
	}
}

void TowerDefense::Aura::MultiShot::Combine(std::shared_ptr<Aura> other)
{
	auto otherMultiShot = std::dynamic_pointer_cast<MultiShot>(other);
	if (otherMultiShot)
	{
		m_ExtraShots += otherMultiShot->GetExtraShots();
		m_InfoText = std::make_unique<Text>("Archers gain + " + std::to_string(m_ExtraShots) + " Multishot", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}