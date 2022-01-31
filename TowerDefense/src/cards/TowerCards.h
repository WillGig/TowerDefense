#pragma once
#include "TowerCard.h"
#include "InfoTile.h"

namespace TowerDefense
{
	class ArcherCard : public TowerCard
	{
	public:
		ArcherCard()
			:TowerCard("Archer", 50, "archerCard", "archerCardUpgraded")
		{
			AddInfoCard(std::make_shared<InfoTile>("SummonInfo"));
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class WizardCard : public TowerCard
	{
	public:
		WizardCard()
			:TowerCard("Wizard", 100, "wizardCard", "wizardCardUpgraded")
		{
			AddInfoCard(std::make_shared<InfoTile>("SummonInfo"));
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class RangerCard : public TowerCard
	{
	public:
		RangerCard()
			:TowerCard("Ranger", 100, "rangerCard", "rangerCardUpgraded")
		{
			AddInfoCard(std::make_shared<InfoTile>("SummonInfo"));
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class GiantCard : public TowerCard
	{
	public:
		GiantCard()
			:TowerCard("Giant", 300, "giantCard", "giantCardUpgraded")
		{
			AddInfoCard(std::make_shared<InfoTile>("SummonInfo"));
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class AlchemistCard : public TowerCard
	{
	public:
		AlchemistCard()
			:TowerCard("Alchemist", 100, "alchemistCard", "alchemistCardUpgraded")
		{
			AddInfoCard(std::make_shared<InfoTile>("SummonInfo"));
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class BardCard : public TowerCard
	{
	public:
		BardCard()
			:TowerCard("Bard", 50, "bardCard", "bardCardUpgraded")
		{
			AddInfoCard(std::make_shared<InfoTile>("SummonInfo"));
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class ClericCard : public TowerCard
	{
	public:
		ClericCard()
			:TowerCard("Cleric", 50, "clericCard", "clericCardUpgraded")
		{
			AddInfoCard(std::make_shared<InfoTile>("SummonInfo"));
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class PaladinCard : public TowerCard
	{
	public:
		PaladinCard()
			:TowerCard("Paladin", 100, "paladinCard", "paladinCardUpgraded")
		{
			AddInfoCard(std::make_shared<InfoTile>("SummonInfo"));
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class ScholarCard : public TowerCard
	{
	public:
		ScholarCard()
			:TowerCard("Scholar", 20, "scholarCard", "scholarCardUpgraded")
		{
			AddInfoCard(std::make_shared<InfoTile>("SummonInfo"));
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};
}