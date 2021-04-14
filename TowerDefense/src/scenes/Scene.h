#pragma once

namespace TowerDefense
{
	enum SceneType { MAINMENU, BASE, PRECOMBAT, COMBAT, POSTCOMBAT };

	class Scene
	{
	public:
		virtual void Render() = 0;
		virtual void Update() = 0;
		virtual void OnSwitch() = 0;
	};
}
