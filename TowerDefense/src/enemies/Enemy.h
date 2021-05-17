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
			Enemy(int width, int height, float health, float speed, const std::string& name);
			void Update() override;
			void Render() override;
			void TakeDamage(float damage, unsigned int source, Tower::DamageType type);
			//Time measured in game updates (60 per second)
			void Slow(float slowPercent, int slowTime);
			void Poison(float poisonDamage, int poisonTime, unsigned int source);
			inline void Stun(int stunTime) { if(stunTime > m_StunTime) m_StunTime = stunTime; };
			inline virtual void SetX(float x) override { m_X = x; m_Image->SetPosition(m_X, m_Y, 0.0f); m_HealthBar->SetPosition(m_X, m_Y + m_Height / 2); }
			inline virtual void SetY(float y) override { m_Y = y; m_Image->SetPosition(m_X, m_Y, 0.0f); m_HealthBar->SetPosition(m_X, m_Y + m_Height / 2); }
			inline void SetSelected(bool selected) { m_Selected = selected; }
			inline float GetHealth() const { return m_Health; }
			inline float GetMaxHealth() const { return m_MaxHealth; }
			inline float GetDistanceTraveled() const { return m_DistanceTraveled; }
			inline float GetSpeed() const { return m_Speed; }

			inline std::string GetName() const { return m_Name; }

			inline bool GetClicked() { return m_Clicked; };

			void SetDistanceTravelled(float distance);

		protected:
			virtual void Destroy();

			int m_Damage;
			static int POISONTICKRATE;
			float m_DistanceTraveled;

		private:
			void Move();
			void FindNewGoal();
			void CheckClicked();
			void UpdateImage();
			void UpdateDebuffs();

			int m_CurrentTile, m_SlowTime, m_PoisonTime, m_PoisonTick, m_StunTime;
			float m_Health, m_MaxHealth, m_Speed, m_SlowPercent, m_PoisonAmount, m_GoalX, m_GoalY;
			bool m_ReachedEnd, m_Selected, m_Clicked;

			unsigned int m_PoisonSource;

			std::string m_Name;

			std::shared_ptr<Image> m_RegularImage, m_SelectedImage;

			std::unique_ptr<HealthBar> m_HealthBar;
		};
	}
}