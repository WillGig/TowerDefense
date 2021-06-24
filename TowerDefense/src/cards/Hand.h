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

		void DiscardCards(int numDiscard);
		void ExhaustCards(int numExhaust);
		inline bool SelectingCards() { return m_CardsToDiscard > (int)m_SelectedCards->size() || m_CardsToExhaust > (int)m_SelectedCards->size(); }

		void DiscardHand();

		inline int GetSize() const { return m_Cards->size(); }

		inline void ResetSelectedCard() { m_SelectedCard = -1; m_Dragging = false; m_ShowingInfo = false; }
		inline void ResetDiscardCard() { m_CardsToDiscard = 0, m_CardsToExhaust = 0; }

		inline int GetSelectedCard() const { return m_SelectedCard; }

		inline bool DraggingCard() const { return m_Dragging; }

		inline bool ShowingCardInfo() const { return m_ShowingInfo; }

		inline std::shared_ptr<Card> GetCurrentPlayingCard() { return m_CurrentPlayingCard; }

	private:
		//Finds the current card being hovered over or clicked
		void FindSelectedCard();
		
		//Checks if a specific card has been selected to discard or exhaust
		//Returns the index of the selected card in the vector of selected cards
		//Returns -1 if the card is not selected
		int CardSelected(int card);

		std::shared_ptr<Card> m_CurrentPlayingCard;

		//m_CardSpacing represents how far apart each card is and gets smaller the more cards are in the hand
		unsigned int m_MaxSize, m_CardSpacing;
		int m_SelectedCard, m_CardsToDiscard, m_CardsToExhaust;
		bool m_Dragging, m_ShowingInfo;
		std::unique_ptr<std::vector<std::shared_ptr<Card>>> m_Cards;

		std::unique_ptr<std::vector<int>> m_SelectedCards;
		std::unique_ptr<Text> m_SelectionText;

		//Fade background when showing card info
		std::unique_ptr<Rectangle> m_Fade;
	};
}