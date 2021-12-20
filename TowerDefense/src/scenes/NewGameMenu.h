#pragma once
#include "Scene.h"

namespace TowerDefense
{
	class NewGameMenu : public Scene
	{
	public:
		NewGameMenu();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
	private:
		std::array<std::unique_ptr<TowerDefense::Button>, 4> m_Buttons;

		std::unique_ptr<Text> m_Title, m_Save1Info, m_Save2Info, m_Save3Info;
	};
}