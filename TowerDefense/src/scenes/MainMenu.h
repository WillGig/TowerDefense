#pragma once
#include "Scene.h"

namespace TowerDefense
{
	class MainMenu : public Scene
	{
	public:
		MainMenu();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
	private:
		std::array<std::unique_ptr<TowerDefense::Button>, 4> m_Buttons;
	};
}
