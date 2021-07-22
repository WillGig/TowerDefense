#pragma once
#include "towers/Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Upgrade : public Button
		{
		public:
			Upgrade(const std::string name, const std::string info);

			void Render() override;
			void SetX(float x) override;
			void SetY(float y) override;

			virtual void UpgradeTower(std::shared_ptr<Tower> t) = 0;

			inline std::string GetName() const { return m_Name; }

		private:
			std::string m_Name;
			std::unique_ptr<Image> m_InfoImage;
			std::unique_ptr<Text> m_InfoText;
		};

		class AttackSpeed : public Upgrade
		{
		public:
			AttackSpeed();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Damage : public Upgrade
		{
		public:
			Damage();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Range : public Upgrade
		{
		public:
			Range();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class MoreMissiles : public Upgrade
		{
		public:
			MoreMissiles();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Crit : public Upgrade
		{
		public:
			Crit();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class ArmorPen : public Upgrade
		{
		public:
			ArmorPen();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Multishot : public Upgrade
		{
		public:
			Multishot();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class MoreFocus : public Upgrade
		{
		public:
			MoreFocus();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Elementalist : public Upgrade
		{
		public:
			Elementalist();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Conjurer : public Upgrade
		{
		public:
			Conjurer();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Necromancer : public Upgrade
		{
		public:
			Necromancer();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Crossbowman : public Upgrade
		{
		public:
			Crossbowman();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class GreyEyes : public Upgrade
		{
		public:
			GreyEyes();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class BBGunner : public Upgrade
		{
		public:
			BBGunner();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class AnimalCompanionUpgrade : public Upgrade
		{
		public:
			AnimalCompanionUpgrade();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Sniper : public Upgrade
		{
		public:
			Sniper();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class LaserBow : public Upgrade
		{
		public:
			LaserBow();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Wings : public Upgrade
		{
		public:
			Wings();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Vengence : public Upgrade
		{
		public:
			Vengence();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class InspiringLeader : public Upgrade
		{
		public:
			InspiringLeader();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class GrenadeGunner : public Upgrade
		{
		public:
			GrenadeGunner();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class TrueAlchemy : public Upgrade
		{
		public:
			TrueAlchemy();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Poisoner : public Upgrade
		{
		public:
			Poisoner();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Pacifist : public Upgrade
		{
		public:
			Pacifist();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Empowerer : public Upgrade
		{
		public:
			Empowerer();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class DisarmingWords : public Upgrade
		{
		public:
			DisarmingWords();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class Lifebringer : public Upgrade
		{
		public:
			Lifebringer();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class BattleCleric : public Upgrade
		{
		public:
			BattleCleric();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class DeathPriest : public Upgrade
		{
		public:
			DeathPriest();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};
	}
}