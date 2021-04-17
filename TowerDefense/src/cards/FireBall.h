#pragma once
#include "Card.h"

namespace TowerDefense
{
	class FireBall : public Card
	{
	public:
		FireBall();
		void Render() override;
		void Update() override;
		void Upgrade() override;
		bool Play() override;
		std::shared_ptr<Card> Clone() override;

	private:
		float m_Damage, m_Radius;

		std::unique_ptr<Circle> m_Circle;
	};
}