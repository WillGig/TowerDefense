#pragma once
#include "Scene.h"
#include "random_events/RandomEvent.h"
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
		static void Reset();
		static void CleanUp();

		static void AddBaseScene(std::shared_ptr<BaseScene> scene);

		static bool ContainsScene(const std::string& name);

		static inline std::shared_ptr<std::vector<std::shared_ptr<BaseScene>>> GetBaseScenes() { return s_BaseScenes; }

	private:
		void UpdateActivities();
		void UpdateNextDay();

		int m_CurrentMenu;

		std::unique_ptr<Button> m_NextDay;

		std::unique_ptr<Text> m_WaitText;

		static std::shared_ptr<std::vector<std::shared_ptr<BaseScene>>> s_BaseScenes;
	};
}