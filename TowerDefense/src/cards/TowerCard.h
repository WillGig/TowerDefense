#pragma once
#include "Card.h"
#include "towers/Tower.h"

namespace TowerDefense
{
	class TowerCard : public Card
	{
	public:
		TowerCard(const std::string& name, int cost, const std::string& image, const std::string& upgradedImage);
		void Render() override;
		void Update() override;
		void Play() override;

	protected:
		virtual std::shared_ptr<Tower::Tower> GetTower() = 0;

		bool m_OverBoard;

	private:
		std::shared_ptr<Tower::Tower> m_HeldTower;
	};
}