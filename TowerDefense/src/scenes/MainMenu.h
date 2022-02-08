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
		std::array<std::unique_ptr<TowerDefense::Button>, 5> m_Buttons;

		std::unique_ptr<Text> m_Title;
	};
}
