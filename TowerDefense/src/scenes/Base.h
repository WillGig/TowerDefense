#pragma once
#include "Scene.h"
#include "cave_scenes/CaveScene.h"
#include "cards/Card.h"
#include "cards/CardChoice.h"
#include "base_scenes/BaseScene.h"

namespace TowerDefense
{
	class Base : public Scene
	{
	public:
		Base();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		static void CleanUp();

		static void AddBaseScene(std::shared_ptr<BaseScene> scene);

		static bool ContainsScene(const std::string& name);

	private:
		void UpdateActivities();
		void UpdateNextDay();

		int m_CurrentMenu;

		bool m_ActivityDone;

		std::unique_ptr<Button> m_NextDay;

		static std::unique_ptr<std::vector<std::shared_ptr<BaseScene>>> s_BaseScenes;
	};
}