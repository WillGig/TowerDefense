#pragma once
#include "Scene.h"
#include "enemies/EnemyIcon.h"
#include "InGameSettings.h"

namespace TowerDefense
{
	class PreCombatScreen : public Scene
	{
	public:
		PreCombatScreen();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
	private:
		bool ContainsEnemy(const std::string& name) const;

		int m_CurrentCardSlot;

		std::unique_ptr<TowerDefense::Button> m_BeginCombat;

		std::unique_ptr<Text> m_IncomingText;

		std::vector<std::unique_ptr<EnemyIcon>> m_Enemies;
	};
}
