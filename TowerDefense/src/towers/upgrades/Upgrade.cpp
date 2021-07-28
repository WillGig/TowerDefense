#include "pch.h"
#include "Upgrade.h"
#include "towers/Wizard.h"
#include "towers/Archer.h"
#include "towers/Monk.h"
#include "towers/Ranger.h"
#include "towers/Paladin.h"
#include "Towers/Alchemist.h"
#include "towers/Bard.h"
#include "towers/Cleric.h"
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

TowerDefense::Tower::Elementalist::Elementalist()
	:Upgrade("elementalistUpgrade", "Gain a powerful\nlightning attack")
{}

void TowerDefense::Tower::Elementalist::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto w = std::dynamic_pointer_cast<Wizard>(t);
	if (w)
		w->SetLightning(true);
	t->SetName("Elementalist");
	t->SetImage("Elementalist");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Conjurer::Conjurer()
	:Upgrade("conjurerUpgrade", "Summon spirits\nto fight for you")
{}

void TowerDefense::Tower::Conjurer::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto w = std::dynamic_pointer_cast<Wizard>(t);
	if (w)
		w->SetSummonner(true);
	t->SetName("Conjurer");
	t->SetImage("Conjurer");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Necromancer::Necromancer()
	:Upgrade("necromancerUpgrade", "Drain life from\nyour enemies")
{}

void TowerDefense::Tower::Necromancer::UpgradeTower(std::shared_ptr<Tower> t)
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

TowerDefense::Tower::Wings::Wings()
	:Upgrade("wingsUpgrade", "Learn to fly")
{}

void TowerDefense::Tower::Wings::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto p = std::dynamic_pointer_cast<Paladin>(t);
	if (p)
		p->SetSpeed(2.0f);

	t->SetName("Winged Paladin");
	t->SetImage("WingedPaladin");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Vengence::Vengence()
	:Upgrade("vengenceUpgrade", "Attacks deal damage to\nall enemies in an area")
{}

void TowerDefense::Tower::Vengence::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto p = std::dynamic_pointer_cast<Paladin>(t);
	if (p)
		p->SetDamageRadius(40.0f);

	t->SetName("Vengence Paladin");
	t->SetImage("VengencePaladin");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::InspiringLeader::InspiringLeader()
	:Upgrade("inspiringLeaderUpgrade", "Critical Strikes cause all\ntowers in range to attack\nfaster for a short time")
{}

void TowerDefense::Tower::InspiringLeader::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto p = std::dynamic_pointer_cast<Paladin>(t);
	if (p)
		p->SetInspiring(true);

	t->SetName("Inspiring Leader");
	t->SetImage("InspiringPaladin");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::GrenadeGunner::GrenadeGunner()
	:Upgrade("grenadeGunnerUpgrade", "Quickly launch\nsmaller grenades")
{}

void TowerDefense::Tower::GrenadeGunner::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto a = std::dynamic_pointer_cast<Alchemist>(t);
	if (a)
	{
		a->SetAttackTime(a->GetAttackTime() * 0.2f);
		a->SetExplosionRadius(a->GetExplosionRadius() - 20);
		a->SetGrenadeSpeed(a->GetGrenadeSpeed() * 2.0f);
	}

	t->SetName("Grenade Gunner");
	t->SetImage("GrenadeGunner");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::TrueAlchemy::TrueAlchemy()
	:Upgrade("trueAlchemyUpgrade", "Turn enemies to gold")
{}

void TowerDefense::Tower::TrueAlchemy::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto a = std::dynamic_pointer_cast<Alchemist>(t);
	if (a)
		a->SetGoldConversion(1);

	t->SetName("True Alchemist");
	t->SetImage("TrueAlchemist");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Poisoner::Poisoner()
	:Upgrade("poisonerUpgrade", "Poisons slow enemies\nand reduce resistances")
{}

void TowerDefense::Tower::Poisoner::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto a = std::dynamic_pointer_cast<Alchemist>(t);
	if (a)
	{
		a->SetSlowPercent(0.7f);
		a->SetResistanceShredPercent(0.25f);
	}

	t->SetName("Poisoner");
	t->SetImage("Poisoner");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Pacifist::Pacifist()
	:Upgrade("pacifistUpgrade", "Slow nearby enemies")
{}

void TowerDefense::Tower::Pacifist::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto b = std::dynamic_pointer_cast<Bard>(t);
	if (b)
		b->SetSlowPercentage(.5f);

	t->SetName("Peace Bard");
	t->SetImage("PeaceBard");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Empowerer::Empowerer()
	:Upgrade("empowererUpgrade", "Buffed towers have\nincreased range and\ncritical damage")
{}

void TowerDefense::Tower::Empowerer::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto b = std::dynamic_pointer_cast<Bard>(t);
	if (b)
	{
		b->SetRangeBuff(25);
		b->SetCritBuff(0.25f);
	}

	t->SetName("Empowerer");
	t->SetImage("Empowerer");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::DisarmingWords::DisarmingWords()
	:Upgrade("disarmingWordsUpgrade", "Debuffs enemies, reducing\nthe damage they deal")
{}

void TowerDefense::Tower::DisarmingWords::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto b = std::dynamic_pointer_cast<Bard>(t);
	if (b)
	{
		b->SetHasAttack(true);
		b->SetAttackTime(b->GetAttackTime() / 2);
	}

	t->SetName("Disarming Bard");
	t->SetImage("DisarmingBard");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::Lifebringer::Lifebringer()
	:Upgrade("lifebringerUpgrade", "Heal every round")
{}

void TowerDefense::Tower::Lifebringer::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto c = std::dynamic_pointer_cast<Cleric>(t);
	if (c)
		c->SetHeal(1);

	t->SetName("Lifebringer Cleric");
	t->SetImage("LifebringerCleric");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::BattleCleric::BattleCleric()
	:Upgrade("battleClericUpgrade", "Attack your enemies!")
{}

void TowerDefense::Tower::BattleCleric::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto c = std::dynamic_pointer_cast<Cleric>(t);
	if (c)
	{
		c->SetHasAttack(true);
		c->SetAttackTime(c->GetAttackTime() / 2);
	}

	t->SetName("Battle Cleric");
	t->SetImage("BattleCleric");
	t->SetLevel(t->GetLevel() + 1);
}

TowerDefense::Tower::DeathPriest::DeathPriest()
	:Upgrade("deathPriestUpgrade", "Lower nearby enemy resistances")
{}

void TowerDefense::Tower::DeathPriest::UpgradeTower(std::shared_ptr<Tower> t)
{
	auto c = std::dynamic_pointer_cast<Cleric>(t);
	if (c)
		c;

	t->SetName("Death Priest");
	t->SetImage("DeathPriest");
	t->SetLevel(t->GetLevel() + 1);
}