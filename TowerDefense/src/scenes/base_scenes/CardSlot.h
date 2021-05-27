#pragma once
#include "cards/Card.h"

namespace TowerDefense
{
	class CardSlot
	{
	public:
		CardSlot(float x, float y, std::shared_ptr<Card> card, int price);
		void Render();
		void Update();
		inline bool CardAvailable() { return m_Card != nullptr; };
		inline bool ShowingInfo() { return m_ShowingInfo; }

	private:
		int m_Price;
		bool m_ShowingInfo;

		std::shared_ptr<Card> m_Card;
		std::unique_ptr<Text> m_PriceText;
		std::unique_ptr<Image> m_GoldImage;
		std::unique_ptr<Rectangle> m_Fade;
	};
}