#include "pch.h"
#include "Upgrade.h"
#include "towers/Wizard.h"

TowerDefense::Tower::Upgrade::Upgrade(const std::string name, const std::string info)
	:Button(0.0f, 0.0f, 50, 50, name), m_Name(name),
	m_InfoImage(std::make_unique<Image>("InfoImage", 0.0f, 0.0f, 220, 100, 180.0f)),
	m_InfoText(std::make_unique<Text>(info, 0.0f, 0.0f, 10.0f, 0.0f))
{
	m_InfoText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::Tower::Upgrade::Render()
{
	Button::Render();
	if (IsSelected())
	{
		m_InfoImage->Render();
		m_InfoText->Render();
	}
}

void TowerDefense::Tower::Upgrade::SetX(float x)
{
	Button::SetX(x);
	m_InfoImage->SetPosition(m_X, m_Y - 80, 0.0f);
	m_InfoText->SetPosition(m_X, m_Y - 90, 0.0f);
}

void TowerDefense::Tower::Upgrade::SetY(float y)
{
	Button::SetY(y);
	m_InfoImage->SetPosition(m_X, m_Y - 80, 0.0f);
	m_InfoText->SetPosition(m_X, m_Y - 90, 0.0f);
}

TowerDefense::Tower::AttackSpeed::AttackSpeed()
	:Upgrade("attackSpeedUpgrade", "Reduce attack time by 25%")
{}

void TowerDefense::Tower::AttackSpeed::UpgradeTower(std::shared_ptr<Tower> t)
{
	t->SetAttackTime(t->GetAttackTime() * 0.75f);
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Damage::Damage()
	:Upgrade("damageUpgrade", "Increase damage by 1")
{}

void TowerDefense::Tower::Damage::UpgradeTower(std::shared_ptr<Tower> t)
{
	t->SetDamage(1.0f + t->GetDamage(t->GetDamageType()), t->GetDamageType());
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Range::Range()
	:Upgrade("rangeUpgrade", "Increase range by 25")
{}

void TowerDefense::Tower::Range::UpgradeTower(std::shared_ptr<Tower> t)
{
	t->SetRange(t->GetRange() + 25);
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::MoreMissiles::MoreMissiles()
	:Upgrade("moreMissilesUpgrade", "Increase number of missiles by 1")
{}

void TowerDefense::Tower::MoreMissiles::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto w = std::dynamic_pointer_cast<Wizard>(t);
	if (w)
		w->SetNumberOfMissiles(w->GetNumberOfMissiles() + 1);
	t->SetLevel(t->GetLevel() + 1);
}