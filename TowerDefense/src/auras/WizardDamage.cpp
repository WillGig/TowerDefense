#include "pch.h"
#include "Aura.h"
#include "cards/TowerCard.h"
#include "towers/Wizard.h"

TowerDefense::Aura::WizardDamage::WizardDamage(float damage)
	:Aura("WizardDamge", "damageUp", "Wizards\ndeal " + Utils::TruncateFloat(damage, 1) + " extra damage"),
	m_Damage(damage)
{}

void TowerDefense::Aura::WizardDamage::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetCardType() == CardType::TOWER)
	{
		auto tower = std::dynamic_pointer_cast<TowerCard>(c)->GetHeldTower();

		auto wizard = std::dynamic_pointer_cast<Tower::Wizard>(tower);

		if (wizard)
			wizard->SetDamage(wizard->GetDamage(Tower::DamageType::MAGIC) + m_Damage, Tower::DamageType::MAGIC);
	}
}

void TowerDefense::Aura::WizardDamage::Combine(std::shared_ptr<Aura> other)
{
	auto otherWizardDamage = std::dynamic_pointer_cast<WizardDamage>(other);
	if (otherWizardDamage)
	{
		m_Damage += otherWizardDamage->GetDamage();
		m_InfoText = std::make_unique<Text>("Wizards deal " + Utils::TruncateFloat(m_Damage, 1) + "\nextra damage", 0.0f, 0.0f, 10.0f, 0.0f);
		m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

const std::string TowerDefense::Aura::WizardDamage::GetSaveData() const
{
	return "Wizard Damage\n" + Utils::TruncateFloat(m_Damage, 1);
}