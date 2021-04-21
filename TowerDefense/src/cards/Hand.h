#pragma once
#include "Card.h"
#include "CardPile.h"

namespace TowerDefense
{
	class Hand
	{

	public:
		Hand(unsigned int maxSize);

		void Render();

		void Update();

		void AddCard(std::shared_ptr<Card> c);

		std::shared_ptr<Card> RemoveCard(int index);

		void UpdateSpacing();

		void DrawCard();

		inline std::shared_ptr<Card> GetCard(int index) const { return m_Cards->at(index); }

		void DiscardHand();

		inline int GetSize() const { return m_Cards->size(); }

		inline void SetSelectedCard(int selectedCard) { m_SelectedCard = selectedCard; }

		inline int GetSelectedCard() const { return m_SelectedCard; }

		inline bool ShowingCardInfo() const { return m_ShowingInfo; }

	private:

		void FindSelectedCard();

		//m_CardSpacing represents how far apart each card is and gets smaller the more cards are in the hand
		unsigned int m_MaxSize, m_CardSpacing;
		int m_SelectedCard;
		bool m_Dragging, m_ShowingInfo;
		std::unique_ptr<std::vector<std::shared_ptr<Card>>> m_Cards;

		//Fade background when showing card info
		std::unique_ptr<Rectangle> m_Fade;
	};
}