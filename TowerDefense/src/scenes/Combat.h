#pragma once
#include "Scene.h"
#include "core/Button.h"
#include "core/Entity.h"
#include "engine/Text.h"
#include "towers/Tower.h"
#include "enemies/Fight.h"
#include "towers/TowerInfo.h"
#include "enemies/EnemyInfo.h"
#include "Auras/Aura.h"

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
		
		static inline void AddEntity(std::shared_ptr<Entity> entity) { s_Adders->push_back(entity); }
		
		static inline void RemoveEntity(int entity) { s_Removers->emplace_back(entity); }
		
		static std::shared_ptr<Entity> GetEntity(unsigned int ID);

		static inline std::shared_ptr<std::vector<std::shared_ptr<Entity>>> GetEntities() { return s_Entities; }

		static void AddAura(std::shared_ptr<Aura> a);
		static void OnCardPlayAuras(std::shared_ptr<Card> c);
		static void OnEnemyHit(unsigned int id, std::shared_ptr<Entity>  source, Tower::DamageType type);
		static void OnEnemyDeath(unsigned int id);

		static inline std::shared_ptr<Fight> GetNextFight() { return s_Fights->at(s_CurrentFight + 1); }
		static inline std::shared_ptr<Fight> GetCurrentFight() { if (s_CurrentFight < 0) return nullptr; return s_Fights->at(s_CurrentFight); }
		
		static inline int GetRoundSpeed() { return s_RoundSpeed; }
		
		static inline bool DraggingInfo() { return (s_TowerInfo && s_TowerInfo->Dragging()) || (s_EnemyInfo && s_EnemyInfo->Dragging()); }
		static inline bool DraggingTowerInfo() { return s_TowerInfo && s_TowerInfo->Dragging(); }
		static inline bool DraggingEnemyInfo() { return s_EnemyInfo && s_EnemyInfo->Dragging(); }

		static inline bool Paused() { return s_Paused; }

		//Called at end of program to clean up memory
		//Necessary to unbind static and singleton GLFW textures before calling glfwTerminate
		static void CleanUp();

	private:

		void RenderCards();

		void UpdateEntities();

		void UpdateAuras();

		void UpdateCards();

		void UpdateWave();

		void UpdateButtons();

		void UpdateSelectedTower();

		void UpdateSelectedEnemy();

		void EndRound();

		bool EnemiesDefeated();

		void ClearProjectilesAndAnimationsAndEnemies();

		void ClearTowers();

		static int s_RoundSpeed;
		static bool s_Paused;

		static int s_CurrentFight;
		Phase m_TurnPhase;
		std::unique_ptr<Button> m_StartButton, m_SpeedButton;
		std::shared_ptr<Tower::Tower> m_SelectedTower;
		std::shared_ptr<Enemy::Enemy> m_SelectedEnemy;

		static std::unique_ptr<TowerInfo> s_TowerInfo;
		static std::unique_ptr<EnemyInfo> s_EnemyInfo;

		static std::shared_ptr<std::vector<std::shared_ptr<Entity>>> s_Entities, s_Adders;
		static std::shared_ptr<std::vector<int>> s_Removers;

		static std::unique_ptr<std::vector<std::shared_ptr<Aura>>> s_Auras;

		static std::unique_ptr<std::vector<std::shared_ptr<Fight>>> s_Fights;
	};
}