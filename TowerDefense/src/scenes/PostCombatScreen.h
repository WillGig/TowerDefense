#pragma once
#include "Scene.h"

namespace TowerDefense
{
	class PostCombatScreen : public Scene
	{
	public:
		PostCombatScreen();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
	private:
		std::unique_ptr<TowerDefense::Button> m_BackToCamp;
	};
}
