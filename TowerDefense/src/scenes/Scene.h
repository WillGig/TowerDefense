#pragma once

namespace TowerDefense
{
	enum SceneType { MAINMENU, SETTINGS, BASE, EVENT, PRECOMBAT, COMBAT, POSTCOMBAT };

	class Scene
	{
	public:
		virtual void Render() = 0;
		virtual void Update() = 0;
		virtual void OnSwitch() = 0;
		static void RenderFade(float alpha);
		static void Init();
		static void CleanUp();

	private:
		static std::unique_ptr<Rectangle> s_Fade;
	};

}
