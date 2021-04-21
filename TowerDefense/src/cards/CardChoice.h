#pragma once
#include "Card.h"

namespace TowerDefense
{
	class CardChoice
	{
	public:
		CardChoice(int numCards, int generationDay);
		CardChoice(std::shared_ptr<std::vector<std::shared_ptr<Card>>> cards, int generationDay);
		void Update();
		void Render();
		inline void SetSelectedCard(int selection) { m_SelectedCard = selection; }
		std::shared_ptr<Card> GetSelectedCard() const;
		void RemoveSelectedCard();
		inline int GetGenerationDay() const { return m_GenerationDay; }
		inline int NumberOfChoices() const { return (int)m_Cards->size(); }

		inline bool ShowingInfo() const { return m_InfoCard != -1; }

	private:
		std::shared_ptr<Card> PickACard();

		int m_SelectedCard, m_InfoCard, m_GenerationDay;

		std::shared_ptr<std::vector<std::shared_ptr<Card>>> m_Cards;

		//Outline around selected Card
		std::unique_ptr<StaticImage> m_Outline;

		//Fade background when rendering card info
		std::unique_ptr<Rectangle> m_Fade;
	};
}