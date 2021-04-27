#pragma once
#include "Scene.h"
#include "cave_scenes/CaveScene.h"
#include "cards/Card.h"
#include "cards/CardChoice.h"
#include "base_scenes/BaseScene.h"

namespace TowerDefense
{
	enum class SubMenu { CAVES, SMITHING, LIBRARY, TAVERN, REST, NONE };

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
		void UpdateActivityDescription();
		void UpdateViewDeck();
		void UpdateNextDay();

		void AddBaseScene(std::shared_ptr<BaseScene> scene);

		int m_CurrentMenu;

		bool m_ActivityDone;

		std::unique_ptr<std::vector<std::shared_ptr<BaseScene>>> m_BaseScenes;

		std::unique_ptr<Button> m_NextDay;

		//String that is set on update to check if description text object needs to be updated
		std::string m_ActivityText;
		std::unique_ptr<Text> m_ActivityDescription;
	};
}