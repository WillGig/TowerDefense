#pragma once
#include "cards/CardPile.h"
#include "cards/Hand.h"
#include "TowerDefense.h"
#include "artifacts/ArtifactPile.h"

namespace TowerDefense 
{
	enum class Resource { WOOD, STONE, WHEAT, GOLD };

	class Player
	{
	public:
		Player(const Player&) = delete;
		static Player& Get();

		void Reset();

		inline int GetEnergy() const { return m_Energy; }
		void SetEnergy(int energy);
		void ChangeEnergy(int change);

		int GetResource(Resource res) const;
		void SetResource(int total, Resource res);
		void ChangeResource(int change, Resource res);

		inline int GetPopulation() const { return m_Population; }
		inline int GetAvailablePopulation() const { return m_Population - m_LumberJacks - m_Miners - m_Farmers; }
		inline void SetPopulation(int pop) { m_Population = pop; }
		inline int GetMaxPopulation() const { return m_MaxPopulation; }
		inline void SetMaxPopulation(int pop) { m_MaxPopulation = pop; }

		int GetWorkers(Resource res) const;
		void AddWorker(Resource res);
		void RemoveWorker(Resource res);

		inline int GetHealth() const { return m_Health; }
		void SetHealth(int health);
		void ChangeHealth(int change);
		inline int GetMaxHealth() const { return m_MaxHealth; }
		void SetMaxHealth(int health);
		void ChangeMaxHealth(int change);

		inline std::shared_ptr<ArtifactPile> GetArtifacts() { return m_Artifacts; }

		void RenderStats();

		void UpdateDayText();

		void SetTextColor(float r, float g, float b, float a);

		void DrawHand();

		void ResetCardPiles();

		inline std::shared_ptr<Hand> GetHand() const { return m_Hand; }
		inline std::shared_ptr<CardPile> GetDrawPile() const { return m_DrawPile; }
		inline std::shared_ptr<CardPile> GetDiscardPile() const { return m_DiscardPile; }

		//Player Deck Controls
		inline void RenderDeck() { m_Deck->RenderCards(); }
		inline void UpdateDeck() { m_Deck->Update(); }
		inline void ShowDeck(bool show) { m_Deck->Show(show); }
		inline bool DeckShowing() { return m_Deck->IsShowing(); }
		inline std::shared_ptr<Card> GetSelectedDeckCard() { return m_Deck->GetSelectedCard(); }
		inline std::shared_ptr<Card> GetClickedDeckCard() { return m_Deck->GetClickedCard(); }
		int GetCardIndex(std::shared_ptr<Card> c);
		void AddToDeck(std::shared_ptr<Card> c);
		void RemoveFromDeck(int index);

		//Player Artifact Controls
		inline bool ArtifactsShowing() { return m_Artifacts->IsShowing(); };
		inline std::shared_ptr<Artifact> GetSelectedArtifact() { return m_Artifacts->GetSelectedArtifact(); };
		void AddToArtifacts(std::shared_ptr<Artifact> a);
		void RemoveFromArtifacts(int index);

		//Prefered method of Rendering and updating deck and artifact buttons and piles in most menus
		void RenderDeckAndArtifacts();
		void UpdateDeckAndArtifacts();

		//Functions to check all artifacts for triggers on respective events
		void ArtifactOnAddCard(std::shared_ptr<Card> c);
		void ArtifactOnRoundStart();
		void ArtifactOnCardPlay(std::shared_ptr<Card> c);
		void ArtifactOnFightStart();
		void ArtifactOnFightEnd();

		//Called at end of program to clean up memory
		//Necessary to unbind static and singleton GLFW textures before calling glfwTerminate
		void CleanUp();

	private:
		Player();

		int m_Health, m_MaxHealth, m_Energy;
		int m_Population, m_MaxPopulation, m_LumberJacks, m_Miners, m_Farmers;
		//Wood, Stone, Wheat, Gold
		Vec4i m_Resources;
		Vec4 m_TextColor;
		std::shared_ptr<Hand> m_Hand;
		std::shared_ptr<CardPile> m_Deck, m_DrawPile, m_DiscardPile;
		std::unique_ptr<Button> m_ViewDeck;
		std::unique_ptr<Text> m_HealthText, m_EnergyText, m_DayText, m_WoodText, m_StoneText, m_WheatText, m_GoldText;
		std::unique_ptr<Image> m_HealthIcon, m_EnergyIcon, m_WoodIcon, m_StoneIcon, m_WheatIcon, m_GoldIcon;
		std::shared_ptr<ArtifactPile> m_Artifacts;
	};
}