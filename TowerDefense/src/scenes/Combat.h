#pragma once
#include "Scene.h"
#include "core/Button.h"
#include "core/Entity.h"
#include "engine/Text.h"
#include "towers/Tower.h"
#include "enemies/Fight.h"

namespace TowerDefense
{
	enum class Phase { START, COMBAT, END };

	class Combat : public Scene
	{
	public:
		Combat();
		
		void Render() override;
		
		void Update() override;
		
		void OnSwitch() override;
		
		static void GenerateFights();
		
		static inline void AddEntity(std::shared_ptr<TowerDefense::Entity> entity) { s_Adders->push_back(entity); }
		
		static inline void RemoveEntity(int entity) { s_Removers->emplace_back(entity); }
		
		static inline auto GetEntities() { return s_Entities; }
		
		static inline int GetRoundSpeed() { return s_RoundSpeed; }
		
		//Called at end of program to clean up memory
		//Necessary to unbind static and singleton GLFW textures before calling glfwTerminate
		static void CleanUp();

	private:

		void RenderCards();

		void UpdateEntities();

		void UpdateCards();

		void UpdateWave();

		void UpdateButtons();

		void UpdateHealthandEnergy();

		void FindSelectedTower();

		void EndRound();

		bool EnemiesDefeated();

		void ClearProjectiles();

		void ClearTowers();

		static int s_RoundSpeed;
		int m_PlayerHealth, m_PlayerEnergy, m_CurrentFight;
		bool m_Paused;
		Phase m_TurnPhase;
		std::unique_ptr<TowerDefense::Button> m_ViewDeck, m_StartButton, m_SpeedButton;
		std::unique_ptr<Text> m_Health, m_Energy, m_Day;
		std::shared_ptr<TowerDefense::Tower::Tower> m_SelectedTower;

		static std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Entity>>> s_Entities, s_Adders;
		static std::shared_ptr<std::vector<int>> s_Removers;

		static std::unique_ptr<std::vector<std::shared_ptr<TowerDefense::Fight>>> s_Fights;
	};
}