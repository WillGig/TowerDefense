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
		std::array<std::unique_ptr<TowerDefense::Button>, 2> m_Buttons;
	};
}