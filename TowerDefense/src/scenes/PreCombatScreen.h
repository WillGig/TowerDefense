#pragma once
#include "Scene.h"

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
		std::unique_ptr<TowerDefense::Button> m_BeginCombat;
	};
}
