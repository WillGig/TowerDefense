#pragma once
#include "Upgrade.h"

namespace TowerDefense
{
	class AttackSpeedUpgrade : public Upgrade
	{
	public:
		AttackSpeedUpgrade(float percent)
			:Upgrade("Attack Speed Upgrade", "attackSpeedUpgrade"), m_Percent(percent)
		{
		}
		void UpgradeHero(HeroCard& hero);

	private:
		float m_Percent;
	};

	class DamageUpgrade : public Upgrade
	{
	public:
		DamageUpgrade(float physicalIncrease, float magicIncrease)
			:Upgrade("Damage Upgrade", "damageUpgrade"), m_PhysicalIncrease(physicalIncrease), m_MagicIncrease(magicIncrease)
		{
		}
		void UpgradeHero(HeroCard& hero);

	private:
		float m_PhysicalIncrease, m_MagicIncrease;
	};

	class RangeUpgrade : public Upgrade
	{
	public:
		RangeUpgrade(int rangeIncrease)
			:Upgrade("Range Upgrade", "rangeUpgrade"), m_RangeIncrease(rangeIncrease)
		{
		}
		void UpgradeHero(HeroCard& hero);

	private:
		int m_RangeIncrease;
	};

	class MoreMissiles : public Upgrade
	{
	public:
		MoreMissiles()
			:Upgrade("More Missiles", "moremissiles")
		{
		}
		void UpgradeHero(HeroCard& hero);
	};
}