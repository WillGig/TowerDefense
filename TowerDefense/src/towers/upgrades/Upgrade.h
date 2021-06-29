#pragma once
#include "towers/Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Upgrade : public Button
		{
		public:
			Upgrade(const std::string name);

			virtual void UpgradeTower(std::shared_ptr<Tower> t) = 0;

			inline std::string GetName() const { return m_Name; }

		private:
			std::string m_Name;
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
	}
}