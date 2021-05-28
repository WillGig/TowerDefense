#pragma once
#include "Scene.h"
#include "enemies/EnemyIcon.h"

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

		std::unique_ptr<TowerDefense::Button> m_BeginCombat;

		std::vector<std::unique_ptr<EnemyIcon>> m_Enemies;
	};
}
