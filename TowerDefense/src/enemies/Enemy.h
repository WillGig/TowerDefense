#pragma once
#include "HealthBar.h"

namespace TowerDefense
{
	namespace Tower
	{
		enum class DamageType;
		class Tower;
	}

	namespace Enemy
	{
		class Enemy : public Entity
		{
		public:
			Enemy(int width, int height, float health, float speed, int goldValue, const std::string& name);
			void Update() override;
			void Render() override;
			virtual void TakeDamage(float damage, unsigned int source, Tower::DamageType type);
			void ChangeHealth(float change);
			//Time measured in game updates (60 per second)
			void Slow(float slowPercent, int slowTime);
			void Poison(float poisonDamage, int poisonTime, unsigned int source);
			void Stun(int stunTime);
			inline virtual void SetX(float x) override { m_X = x; m_Image->SetPosition(m_X, m_Y, 0.0f); m_HealthBar->SetPosition(m_X, m_Y + m_Height / 2); }
			inline virtual void SetY(float y) override { m_Y = y; m_Image->SetPosition(m_X, m_Y, 0.0f); m_HealthBar->SetPosition(m_X, m_Y + m_Height / 2); }
			inline void SetSelected(bool selected) { m_Selected = selected; }
			inline float GetHealth() const { return m_Health; }
			inline float GetMaxHealth() const { return m_MaxHealth; }
			inline void SetArmor(float armor) { m_Armor = armor; }
			inline float GetArmor() const { return m_Armor; }
			inline void SetMagicResistance(float magicResistance) { m_MagicResistance = magicResistance; }
			inline float GetMagicResistance() const { return m_MagicResistance; }
			inline float GetDistanceTraveled() const { return m_DistanceTraveled; }
			inline float GetSpeed() const { return m_Speed; }
			inline int GetGoldValue() const { return m_GoldValue; }

			inline bool Visible() const { return m_Visible; }

			inline std::string GetName() const { return m_Name; }

			inline bool GetClicked() { return m_Clicked; };

			void SetDistanceTravelled(float distance);

		protected:
			virtual void Move();
			void FindNewGoal(float x, float y);
			virtual void Destroy();

			int m_CurrentTile, m_Damage;
			static int POISONTICKRATE;
			float m_Health, m_MaxHealth, m_Armor, m_MagicResistance, m_DistanceTraveled, m_GoalX, m_GoalY;
			bool m_Visible, m_ReachedEnd;

			std::shared_ptr<Image> m_RegularImage, m_SelectedImage;

		private:
			void CheckClicked();
			void UpdateImage();
			void UpdateDebuffs();

			int m_GoldValue, m_SlowTime, m_PoisonTime, m_PoisonTick, m_StunTime;
			float m_Speed, m_SlowPercent, m_PoisonAmount, m_StunResist;
			bool m_Selected, m_Clicked;

			unsigned int m_PoisonSource;

			std::string m_Name;

			std::unique_ptr<HealthBar> m_HealthBar;
		};
	}
}