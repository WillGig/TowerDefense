#pragma once
#include "TowerCard.h"

namespace TowerDefense
{
	class ArcherCard : public TowerCard
	{
	public:
		ArcherCard()
			:TowerCard("Archer", 50, "res/textures/archerCard.png", "res/textures/archerCardUpgraded.png")
		{
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class WizardCard : public TowerCard
	{
	public:
		WizardCard()
			:TowerCard("Wizard", 100, "res/textures/wizardCard.png", "res/textures/wizardCardUpgraded.png")
		{
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class GiantCard : public TowerCard
	{
	public:
		GiantCard()
			:TowerCard("Giant", 300, "res/textures/giantCard.png", "res/textures/giantCardUpgraded.png")
		{
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class AlchemistCard : public TowerCard
	{
	public:
		AlchemistCard()
			:TowerCard("Alchemist", 100, "res/textures/alchemistCard.png", "res/textures/alchemistCardUpgraded.png")
		{
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class BardCard : public TowerCard
	{
	public:
		BardCard()
			:TowerCard("Bard", 100, "res/textures/bardCard.png", "res/textures/bardCardUpgraded.png")
		{
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class ClericCard : public TowerCard
	{
	public:
		ClericCard()
			:TowerCard("Cleric", 100, "res/textures/clericCard.png", "res/textures/clericCardUpgraded.png")
		{
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class PaladinCard : public TowerCard
	{
	public:
		PaladinCard()
			:TowerCard("Paladin", 100, "res/textures/paladinCard.png", "res/textures/paladinCardUpgraded.png")
		{
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};

	class MonkCard : public TowerCard
	{
	public:
		MonkCard()
			:TowerCard("Monk", 100, "res/textures/monkCard.png", "res/textures/monkCardUpgraded.png")
		{
		}
		std::shared_ptr<Card> Clone() override;

	protected:
		std::shared_ptr<Tower::Tower> GetTower() override;
	};
}