#pragma once
#include "Scene.h"

namespace TowerDefense
{
	class InGameSettings : public Scene
	{
	public:
		void Render() override;
		void Update() override;
		void OnSwitch() override;

		inline const bool IsShowing() { return m_Showing; }
		inline void Show(bool show) { m_Showing = show; OnSwitch(); }

		inline void RenderButton() { m_SettingsButton->Render(); }
		void UpdateButton();

		void CleanUp();

		static InGameSettings& Get();

	private:
		InGameSettings();

		bool m_Showing;

		std::unique_ptr<Rectangle> m_Background;

		std::shared_ptr<Button> m_SettingsButton;
		std::unique_ptr<Button> m_MainMenu;
	};
}