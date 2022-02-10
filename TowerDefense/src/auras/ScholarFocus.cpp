#include "pch.h"
#include "Aura.h"
#include "cards/TowerCard.h"
#include "towers/Scholar.h"

TowerDefense::Aura::ScholarFocus::ScholarFocus(int num)
	:Aura("ScholarFocus", "focusUp", "Scholars\ngenerate " + std::to_string(num) + " extra Focus"),
	m_Num(num)
{}

void TowerDefense::Aura::ScholarFocus::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetCardType() == CardType::TOWER)
	{
		auto tower = std::dynamic_pointer_cast<TowerCard>(c)->GetHeldTower();
		auto scholar = std::dynamic_pointer_cast<Tower::Scholar>(tower);

		if (scholar)
			scholar->SetNumberOfFocus(scholar->GetNumberOfFocus() + m_Num);
	}
}

void TowerDefense::Aura::ScholarFocus::Combine(std::shared_ptr<Aura> other)
{
	auto otherScholarFocus = std::dynamic_pointer_cast<ScholarFocus>(other);
	if (otherScholarFocus)
	{
		m_Num += otherScholarFocus->GetNum();
		m_InfoText = std::make_unique<Text>("Scholars\ngenerate " + std::to_string(m_Num) + " extra Focus", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

const std::string TowerDefense::Aura::ScholarFocus::GetSaveData() const
{
	return "Scholar Focus\n" + std::to_string(m_Num);
}