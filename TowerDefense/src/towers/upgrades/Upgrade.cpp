#include "pch.h"
#include "Upgrade.h"
#include "towers/Wizard.h"
#include "towers/Archer.h"
#include "towers/Monk.h"
#include "towers/Ranger.h"
#include "towers/AnimalCompanion.h"

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
	:Upgrade("rangeUpgrade", "Increase range by 50")
{}

void TowerDefense::Tower::Range::UpgradeTower(std::shared_ptr<Tower> t)
{
	t->SetRange(t->GetRange() + 50);
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::MoreMissiles::MoreMissiles()
	:Upgrade("moreMissilesUpgrade", "Increase number of\nmissiles by 1")
{}

void TowerDefense::Tower::MoreMissiles::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto w = std::dynamic_pointer_cast<Wizard>(t);
	if (w)
		w->SetNumberOfMissiles(w->GetNumberOfMissiles() + 1);
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Crit::Crit()
	:Upgrade("critUpgrade", "Increase critical\nchance by 25%")
{}

void TowerDefense::Tower::Crit::UpgradeTower(std::shared_ptr<Tower> t)
{
	t->SetCritChance(t->GetCritChance() + .25f);
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::ArmorPen::ArmorPen()
	:Upgrade("armorPenUpgrade", "+20% Change to reduce\nenemy armor by 50%")
{}

void TowerDefense::Tower::ArmorPen::UpgradeTower(std::shared_ptr<Tower> t)
{
	t->SetArmorPenChance(t->GetArmorPenChance() + .2f);
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Multishot::Multishot()
	:Upgrade("multishotUpgrade", "Fire 1 additional arrow")
{}

void TowerDefense::Tower::Multishot::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto a = std::dynamic_pointer_cast<Archer>(t);
	if (a)
		a->SetNumberOfArrows(a->GetNumberOfArrows() + 1);
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::MoreFocus::MoreFocus()
	:Upgrade("moreFocusUpgrade", "Add an additional\nFocus to your hand\neach round")
{}

void TowerDefense::Tower::MoreFocus::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto m = std::dynamic_pointer_cast<Monk>(t);
	if (m)
		m->SetNumberOfFocus(m->GetNumberOfFocus() + 1);
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::WizardElementalist::WizardElementalist()
	:Upgrade("elementalistUpgrade", "Gain a powerful\nlightning attack")
{}

void TowerDefense::Tower::WizardElementalist::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto w = std::dynamic_pointer_cast<Wizard>(t);
	if (w)
		w->SetLightning(true);
	t->SetName("Elementalist");
	t->SetImage("Elementalist");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::WizardConjurer::WizardConjurer()
	:Upgrade("conjurerUpgrade", "Summon spirits\nto fight for you")
{}

void TowerDefense::Tower::WizardConjurer::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto w = std::dynamic_pointer_cast<Wizard>(t);
	if (w)
		w->SetSummonner(true);
	t->SetName("Conjurer");
	t->SetImage("Conjurer");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::WizardNecromancer::WizardNecromancer()
	:Upgrade("necromancerUpgrade", "Drain life from\nyour enemies")
{}

void TowerDefense::Tower::WizardNecromancer::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto w = std::dynamic_pointer_cast<Wizard>(t);
	if (w)
		w->SetGraveMissileFrequency(3);
	t->SetName("Necromancer");
	t->SetImage("Necromancer");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Crossbowman::Crossbowman()
	:Upgrade("crossbowmanUpgrade", "Slow, piercing shot")
{}

void TowerDefense::Tower::Crossbowman::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto a = std::dynamic_pointer_cast<Archer>(t);
	if (a)
	{
		a->SetPierce(3);
		a->SetDamage(a->GetDamage(DamageType::PHYSICAL) + 3, DamageType::PHYSICAL);
		a->SetAttackTime(a->GetAttackTime() * 3);
	}

	t->SetName("Crossbowman");
	t->SetImage("Crossbowman");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::GreyEyes::GreyEyes()
	:Upgrade("greyEyesUpgrade", "Arrows seek out\ntheir targets")
{}

void TowerDefense::Tower::GreyEyes::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto a = std::dynamic_pointer_cast<Archer>(t);
	if (a)
		a->SetTurnRate(3.0f);

	t->SetName("Grey Eyes");
	t->SetImage("GreyEyes");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::BBGunner::BBGunner()
	:Upgrade("bbGunnerUpgrade", "Rapid fire attacks\nwith lower damage")
{}

void TowerDefense::Tower::BBGunner::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto a = std::dynamic_pointer_cast<Archer>(t);
	if (a)
	{
		a->SetAttackTime(a->GetAttackTime()/10.0f);
		a->SetDamageModifier(0.2f);
	}
		
	t->SetName("BB Gunner");
	t->SetImage("BBGunner");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::AnimalCompanionUpgrade::AnimalCompanionUpgrade()
	:Upgrade("animalCompanionUpgrade", "Summon an \nanimal companion\nto fight for you")
{}

void TowerDefense::Tower::AnimalCompanionUpgrade::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto r = std::dynamic_pointer_cast<Ranger>(t);
	if (r)
		r->SetCompanion(std::make_shared<AnimalCompanion>(1.0f, 30.0f, 200, 1.0f, "Falcon", t));

	t->SetName("Beast Master");
	t->SetImage("AnimalCompanion");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Sniper::Sniper()
	:Upgrade("sniperUpgrade", "Massive Range and\nslow, deadly attack")
{}

void TowerDefense::Tower::Sniper::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto r = std::dynamic_pointer_cast<Ranger>(t);
	if (r)
	{
		r->SetAttackTime(r->GetAttackTime() * 4.0f);
		r->SetCritChance(r->GetCritChance() + .25f);
		r->SetRange(r->GetRange() + 200);
		r->SetCritMultiplier(4.0f);
	}

	t->SetName("Sniper");
	t->SetImage("Sniper");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::LaserBow::LaserBow()
	:Upgrade("laserBowUpgrade", "Laser-Bow")
{}

void TowerDefense::Tower::LaserBow::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto r = std::dynamic_pointer_cast<Ranger>(t);
	if (r)
	{
		r->SetLaser(true);
		r->SetAttackTime(r->GetAttackTime() / 10.0f);
	}
		

	t->SetName("Laser Bowman");
	t->SetImage("LaserBow");
	t->SetLevel(t->GetLevel() + 1);
}