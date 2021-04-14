#pragma once
#include "Card.h"

namespace TowerDefense
{
	class FrostBall : public Card
	{
	public:
		FrostBall();
		void Render() override;
		void Update() override;
		void Upgrade() override;
		void Play() override;
		std::shared_ptr<Card> Clone() override;

	private:
		float m_SlowPercent, m_Radius;
		int m_SlowTime;
		bool m_OverBoard;

		std::unique_ptr<Circle> m_Circle;
	};
}