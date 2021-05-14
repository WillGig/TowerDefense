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
		bool CanPlay() override;
		void Play() override;
		void Upgrade() override;

	protected:
		virtual std::shared_ptr<Tower::Tower> GetTower() = 0;

	private:
		std::shared_ptr<Tower::Tower> m_HeldTower;
	};
}