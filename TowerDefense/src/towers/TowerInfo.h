#pragma once
#include "Tower.h"

namespace TowerDefense
{
	class TowerInfo : public Entity
	{
	public:
		TowerInfo(float x, float y, std::shared_ptr<Tower::Tower> t);
		void Render() override;
		void Update() override;

		void SetX(float x) override;
		void SetY(float y) override;

		inline bool Dragging() { return m_Dragging; }
		inline bool Upgrading() { return m_Upgrading; }

	private:
		void UpdateTargetText();
		void UpdateStatsText();

		bool m_Dragging, m_Upgrading;
		float m_PreviousMouseX, m_PreviousMouseY, m_TowerDamage, m_TowerAttackSpeed, m_TowercritChance, m_TowerDamageDealt;
		int m_TowerRange, m_TowerLevel, m_UpgradeCost;

		std::unique_ptr<Text> m_Name, m_Target, m_Stats, m_StatsNumbers, m_Level, m_UpgradeText;

		std::unique_ptr<Image> m_EnergyIcon;

		std::unique_ptr<Button> m_TargetLeft, m_TargetRight, m_UpgradeButton;

		std::shared_ptr<Tower::Tower> m_Tower;
	};
}