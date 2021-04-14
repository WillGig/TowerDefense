#pragma once
#include "Scene.h"
#include "cards/Card.h"
#include "cards/CardChoice.h"

namespace TowerDefense
{
	enum class SubMenu { SMITHING, LIBRARY, TAVERN, NONE };

	class Base : public Scene
	{
	public:
		Base();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
	private:
		void RenderSmithing();
		void RenderLibrary();
		void RenderTavern();
		void UpdateSmithing();
		void UpdateLibrary();
		void UpdateTavern();
		void UpdateDeck();
		void UpdateActivities();
		void UpdateActivityDescription();
		void UpdateViewDeck();
		void UpdateNextDay();

		void FindSelectedCard();

		SubMenu m_SubMenu;

		bool m_ActivityDone;

		std::array<std::unique_ptr<TowerDefense::Button>, 10> m_Buttons;

		//String that is set on update to check if description text object needs to be updated
		std::string m_ActivityText;
		Text m_ActivityDescription;

		//Selected card that is shown in smithing menu
		std::shared_ptr<Card> m_SelectedCard, m_SelectedCardImage;

		//Card choices shown in library and tavern
		std::unique_ptr<TowerDefense::CardChoice> m_CardChoice, m_TavernChoice;

		std::unique_ptr<TowerDefense::StaticImage> m_SmithingArrow;

		//Background fade when showing selected upgrade in smithing menu
		std::unique_ptr<Rectangle> m_Fade;
	};
}