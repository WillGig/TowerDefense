#pragma once
#include "Scene.h"

namespace TowerDefense
{
	class Settings : public Scene
	{
	public:
		Settings();
		void Update() override;
		void Render() override;
		void OnSwitch() override;
	private:
		std::array<std::unique_ptr<TowerDefense::Button>, 3> m_Buttons;

		//no other buttons should be interactable while button requires focus e.g. dropdown menu
		int m_FocusedButton;
	};
}