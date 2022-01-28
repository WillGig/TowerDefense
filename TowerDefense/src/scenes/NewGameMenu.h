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
		bool m_Confirming;
		int m_ConfirmingSlot;

		std::array<std::unique_ptr<TowerDefense::Button>, 9> m_Buttons;

		std::unique_ptr<Text> m_Title, m_Save1Info, m_Save2Info, m_Save3Info, m_ConfirmText;

		std::unique_ptr<Rectangle> m_Fade;
	};
}