#pragma once
#include "Card.h"

namespace TowerDefense
{
	class CardPile : public TowerDefense::Entity
	{
	public:
		CardPile(float x, float y);

		void Update() override;

		void RenderCards();

		void AddCard(std::shared_ptr<Card> c);

		std::shared_ptr<Card> RemoveCard(int index);

		std::shared_ptr<Card> GetSelectedCard();

		std::shared_ptr<Card> GetClickedCard();

		void Transfer(std::shared_ptr<CardPile> p);

		void Copy(std::shared_ptr<CardPile> p);

		void Clear();

		void Shuffle();

		inline std::shared_ptr<Card> GetCard(int index) const { return m_Cards->at(index); }

		inline void Show(bool showing) { m_Showing = showing; m_Scroll = 0; }

		inline bool IsShowing() const { return m_Showing; }

		inline void SetOrdered(bool ordered) { m_Ordered = ordered; }

		inline int GetSize() const { return m_Cards->size(); }

	private:
		void Swap(int i, int j);

		void Randomize();

		//Scroll offset when viewing cardpile
		int m_Scroll, m_SelectedCard;

		bool m_Showing;
		//Whether the pile is shown in order or random. Ordered by default
		bool m_Ordered;

		std::unique_ptr<std::vector<std::shared_ptr<Card>>> m_Cards;

		//Order that cards are shown in if randomized
		std::vector<int> m_RandomOrder;

		std::shared_ptr<Image> m_FullImage, m_EmptyImage;

		//Fade background when rendering card list
		std::unique_ptr<Rectangle> m_Fade;
	};
}