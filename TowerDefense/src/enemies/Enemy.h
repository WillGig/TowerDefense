#pragma once
#include "HealthBar.h"
#include "States/State.h"

namespace TowerDefense
{
	namespace Tower
	{
		enum class DamageType;
		class Tower;
	}

	namespace Enemy
	{
		class State;

		class Enemy : public Entity
		{
		public:
			Enemy(int width, int height, float health, float speed, int goldValue, const std::string& name, int damage);
			void Update() override;
			void Render() override;
			virtual void TakeDamage(float damage, unsigned int source, Tower::DamageType type);
			void ChangeHealth(float change);
			//Time measured in game updates (60 per second)
			void ApplyState(std::shared_ptr<State> s);
			//void Poison(float poisonDamage, int poisonTime, unsigned int source);
			virtual void SetX(float x) override;
			virtual void SetY(float y) override;
			inline void SetSelected(bool selected) { m_Selected = selected; }
			inline float GetHealth() const { return m_Health; }
			inline float GetMaxHealth() const { return m_MaxHealth; }
			inline void SetArmor(float armor) { m_Armor = armor; }
			inline float GetArmor() const { return m_Armor; }
			inline void SetMagicResistance(float magicResistance) { m_MagicResistance = magicResistance; }
			inline float GetMagicResistance() const { return m_MagicResistance; }
			inline float GetDistanceTraveled() const { return m_DistanceTraveled; }
			inline void SetSpeed(float speed) { m_Speed = speed; }
			inline float GetSpeed() const { return m_Speed; }
			inline int GetGoldValue() const { return m_GoldValue; }

			inline std::string GetName() const { return m_Name; }

			inline bool GetClicked() { return m_Clicked; };

			void SetDistanceTravelled(float distance);

			inline int GetBounty() const { return m_Bounty; };
			inline void SetBounty(int bounty) { m_Bounty = bounty; }

			inline int GetDamage() const { return m_Damage; }
			void SetDamage(int damage);

			inline void SetStunned(bool stunned) { m_Stunned = stunned; if(stunned) m_StunResist += 1.0f; }

			inline float GetStunResist() const { return m_StunResist; }

			void SetPoisonPercent(float percent);

		protected:
			virtual void Move();
			void FindNewGoal(float x, float y);
			virtual void Destroy();

			int m_CurrentTile, m_Damage;
			float m_Health, m_MaxHealth, m_Armor, m_MagicResistance, m_DistanceTraveled, m_GoalX, m_GoalY;
			bool m_ReachedEnd;

			std::shared_ptr<Image> m_RegularImage, m_SelectedImage;

		private:
			void CheckClicked();
			void UpdateImage();
			void UpdateDebuffs();

			int m_GoldValue, m_Bounty;
			float m_Speed, m_StunResist, m_PoisonPercent;
			bool m_Selected, m_Clicked, m_Stunned;

			std::string m_Name;

			std::unique_ptr<HealthBar> m_HealthBar;

			std::unique_ptr<Image> m_DamageIcon;
			std::unique_ptr<Text> m_DamageText;

			std::vector<std::shared_ptr<State>> m_States;
		};
	}
}