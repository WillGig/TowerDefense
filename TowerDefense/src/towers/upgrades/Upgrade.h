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

		class WizardElementalist : public Upgrade
		{
		public:
			WizardElementalist();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class WizardConjurer : public Upgrade
		{
		public:
			WizardConjurer();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};

		class WizardNecromancer : public Upgrade
		{
		public:
			WizardNecromancer();

			void UpgradeTower(std::shared_ptr<Tower> t) override;
		};
	}
}