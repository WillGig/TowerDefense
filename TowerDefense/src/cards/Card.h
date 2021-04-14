#pragma once

namespace TowerDefense
{
	class Card : public TowerDefense::Entity
	{
	public:
		Card(std::string name, int cost, const std::string& image, const std::string& upgradedImage);

		virtual void Play();

		void Update() override;

		void RenderUpgrade(float x, float y);

		virtual void Upgrade();

		virtual std::shared_ptr<Card> Clone() = 0;

		inline std::string GetName() const { return m_Name; }

		inline int GetHandPosition() const { return m_HandPosition; }
		inline void SetHandPosition(int position) { m_HandPosition = position; }

		inline int GetCost() const { return m_Cost; }
		inline void SetCost(int cost) { m_Cost = cost; }

		inline bool IsUpgraded() const { return m_Upgraded; }

		static std::shared_ptr<Card> GetCommonCard();
		static std::shared_ptr<Card> GetUncommonCard();
		static std::shared_ptr<Card> GetRareCard();

		static inline float GetUncommonChance() { return s_UncommonCardChance; }
		static inline float GetRareChance() { return s_RareCardChance; }

	private:
		std::string m_Name;

		//Index of card in hand 0 being the leftmost card
		int m_HandPosition;

		//Chances for randomly generated cards
		static float s_UncommonCardChance, s_RareCardChance;

	protected:
		int m_Cost;
		bool m_Upgraded;
		//Whether or not the card enters the discard pile after being played
		//Cards that exhaust DO NOT enter the discard pile. False by default for non-hero cards
		bool m_Exhausts;
		std::shared_ptr<Image> m_UpgradedImage;
	};
}