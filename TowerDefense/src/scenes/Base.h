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

	private:
		void UpdateDeck();
		void UpdateActivities();
		void UpdateViewDeck();
		void UpdateNextDay();

		void AddBaseScene(std::shared_ptr<BaseScene> scene);

		int m_CurrentMenu;

		bool m_ActivityDone;

		std::unique_ptr<std::vector<std::shared_ptr<BaseScene>>> m_BaseScenes;

		std::unique_ptr<Button> m_NextDay;
	};
}