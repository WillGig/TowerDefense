#pragma once
#include "cards/CardPile.h"
#include "cards/Hand.h"
#include "TowerDefense.h"

namespace TowerDefense 
{
	class Player
	{
	public:
		Player(const Player&) = delete;
		static Player& Get();

		inline int GetEnergy() const { return m_Energy; }
		inline void SetEnergy(int energy) { m_Energy = energy; }
		void ChangeEnergy(int change);

		inline int GetHealth() const { return m_Health; }
		void ChangeHealth(int change);

		inline int GetMaxHealth() const { return m_MaxHealth; }
		void ChangeMaxHealth(int change);

		inline void RenderDeckButton() { m_ViewDeck->Render(); }
		inline void UpdateDeckButton() { m_ViewDeck->Update(); }
		inline bool DeckButtonClicked() { return m_ViewDeck->IsClicked(); }

		inline void RenderHealth() { m_HealthText->Render(); }
		inline void RenderEnergy() { m_EnergyText->Render(); }
		inline void RenderDay() { m_DayText->Render(); }

		void UpdateDayText();

		void SetTextColor(float r, float g, float b, float a);

		void DrawHand();

		void ResetCardPiles();

		inline std::shared_ptr<Hand> GetHand() const { return m_Hand; }
		inline std::shared_ptr<CardPile> GetDeck() const { return m_Deck; }
		inline std::shared_ptr<CardPile> GetDrawPile() const { return m_DrawPile; }
		inline std::shared_ptr<CardPile> GetDiscardPile() const { return m_DiscardPile; }

		//Called at end of program to clean up memory
		//Necessary to unbind static and singleton GLFW textures before calling glfwTerminate
		void CleanUp();

	private:
		Player();

		int m_Health, m_MaxHealth, m_Energy;
		Vec4 m_TextColor;
		std::shared_ptr<Hand> m_Hand;
		std::shared_ptr<CardPile> m_Deck, m_DrawPile, m_DiscardPile;
		std::unique_ptr<Button> m_ViewDeck;
		std::unique_ptr<Text> m_HealthText, m_EnergyText, m_DayText;
	};
}