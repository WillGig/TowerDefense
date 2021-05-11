#pragma once
#include "BaseScene.h"

namespace TowerDefense
{
	class BaseScene;

	class BuildButton
	{
	public:
		BuildButton(const std::string& button, Vec4i cost, std::shared_ptr<BaseScene> scene);
		void Update();
		void Render();
		void SetPosition(float x, float y);
		inline Vec4i GetCost() { return m_Cost; }
		inline bool Clicked() { return m_Button->IsClicked(); }
		inline std::shared_ptr<BaseScene> GetScene() { return m_Scene; };

	private:
		Vec4i m_Cost;
		std::shared_ptr<BaseScene> m_Scene;
		std::unique_ptr<Button> m_Button;
		std::unique_ptr<Text> m_WoodCost, m_StoneCost, m_WheatCost;
		std::unique_ptr<Image> m_WoodImage, m_StoneImage, m_WheatImage;
	};
}