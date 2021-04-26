#pragma once
#include "cards/CardPile.h"
#include "cards/Hand.h"

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
		inline void ChangeMaxHealth(int change) { m_MaxHealth += change; if (m_Health > m_MaxHealth) m_Health = m_MaxHealth; }

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
		std::shared_ptr<Hand> m_Hand;
		std::shared_ptr<CardPile> m_Deck, m_DrawPile, m_DiscardPile;
	};
}