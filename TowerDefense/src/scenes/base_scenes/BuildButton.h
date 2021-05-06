#pragma once
#include "BaseScene.h"

namespace TowerDefense
{
	class BaseScene;

	class BuildButton
	{
	public:
		BuildButton(const std::string& button, int cost, std::shared_ptr<BaseScene> scene);
		void Update();
		void Render();
		void SetPosition(float x, float y);
		inline int GetCost() { return m_Cost; }
		inline bool Clicked() { return m_Button->IsClicked(); }
		inline std::shared_ptr<BaseScene> GetScene() { return m_Scene; };

	private:
		int m_Cost;
		std::shared_ptr<BaseScene> m_Scene;
		std::unique_ptr<Button> m_Button;
		std::unique_ptr<Text> m_Text;
		std::unique_ptr<Image> m_CoinImage;
	};
}