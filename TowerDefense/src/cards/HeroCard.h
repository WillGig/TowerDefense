#pragma once
#include "TowerCard.h"
#include "CardChoice.h"
#include "quirks/Quirk.h"


namespace TowerDefense
{
	namespace Quirk
	{
		class Quirk;
	}
	
	class HeroCard : public TowerCard
	{
	public:
		HeroCard(const std::string& name, const std::string& text, int cost, const std::string& texture, std::shared_ptr<Tower::Tower> tower, std::shared_ptr<std::vector<std::shared_ptr<Quirk::Quirk>>> quirks);
		void Render() override;
		void Upgrade() override;
		bool Play() override;
		std::shared_ptr<Card> Clone() override;

		inline int GetLevel() const { return m_Level; }
		inline std::shared_ptr<CardChoice> GetUpgrades() const { return m_Upgrades; }
		inline std::shared_ptr<Tower::Tower> GetTower() override { return m_Tower; }
		inline void SetTower(std::shared_ptr<Tower::Tower> t) { m_Tower = t; }
		inline void SetQuirks(std::shared_ptr<std::vector<std::shared_ptr<Quirk::Quirk>>> quirks) { m_Quirks = quirks; }
		inline void SetLevel(int level) { m_Level = level; }

		void SetX(float x) override;
		void SetY(float y) override;
		void SetRotation(float rotation) override;


		static std::shared_ptr<HeroCard> GenerateHero();

	private:
		static std::string GenerateText(std::shared_ptr<std::vector<std::shared_ptr<Quirk::Quirk>>> quirks, const std::string& heroClass);

		int m_Level;

		std::string m_CardText;

		std::unique_ptr<Text> m_NameText, m_BodyText;

		std::shared_ptr<Tower::Tower> m_Tower;

		std::shared_ptr<std::vector<std::shared_ptr<Quirk::Quirk>>> m_Quirks;

		std::shared_ptr<CardChoice> m_Upgrades;
	};
}