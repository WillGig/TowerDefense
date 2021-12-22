#pragma once
#include "Scene.h"

namespace TowerDefense
{
	class InGameSettings : public Scene
	{
	public:
		InGameSettings();
		void Render() override;
		void Update() override;
		void OnSwitch() override;

		inline const bool IsShowing() { return m_Showing; }
		inline void Show(bool show) { m_Showing = show; OnSwitch(); }

	private:
		bool m_Showing;

		std::unique_ptr<Rectangle> m_Background;

		std::unique_ptr<Button> m_Close, m_MainMenu;
	};
}