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
		std::shared_ptr<Card> GetSelectedCard() const;
		void RemoveSelectedCard();
		inline int GetGenerationDay() const { return m_GenerationDay; }

	private:
		std::shared_ptr<Card> PickACard();

		int m_SelectedCard, m_GenerationDay;

		std::shared_ptr<std::vector<std::shared_ptr<Card>>> m_Cards;

		//Outline around selected Card
		std::unique_ptr<StaticImage> m_Outline;
	};
}