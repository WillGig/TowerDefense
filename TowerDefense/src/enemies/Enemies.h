#pragma once
#include "Enemy.h"

namespace TowerDefense
{
	namespace Enemy
	{
		class Rat : public Enemy
		{
		public:
			Rat()
				:Enemy(32, 32, 10.0f, 1.0f, "Rat")
			{}
		};

		class GiantRat : public Enemy
		{
		public:
			GiantRat()
				:Enemy(32, 32, 50.0f, 0.75f, "Giant Rat")
			{}
		};

		class BossRat : public Enemy
		{
		public:
			BossRat()
				:Enemy(64, 64, 500.0f, 0.3f, "Boss Rat")
			{
				m_Armor = 200;
				m_MagicResistance = 200;
				m_Damage = 20;
			}
		};

		class Goblin : public Enemy
		{
		public:
			Goblin()
				:Enemy(32, 32, 25.0f, 1.0f, "Goblin")
			{
				m_Armor = 20;
				m_MagicResistance = 20;
			}
		};

		class Orc : public Enemy
		{
		public:
			Orc()
				:Enemy(32, 32, 50.0f, 0.8f, "Orc ")
			{
				m_Armor = 50;
				m_MagicResistance = 50;
			}
		};

		class Beetle : public Enemy
		{
		public:
			Beetle()
				:Enemy(32, 32, 4.0f, 2.0f, "Beetle")
			{}
		};

		class Slime : public Enemy
		{
		public:
			Slime()
				:Enemy(32, 32, 13.0f, 0.7f, "Slime")
			{}
		};

		class Spider : public Enemy
		{
		public:
			Spider()
				:Enemy(32, 32, 20.0f, 1.0f, "Spider")
			{}
		};

		class ToughBeetle : public Enemy
		{
		public:
			ToughBeetle()
				:Enemy(32, 32, 40.0f, 0.5f, "Tough Beetle")
			{
				m_Armor = 100;
			}
		};

		class Ooze : public Enemy
		{
		public:
			Ooze()
				:Enemy(32, 32, 40.0f, 0.7f, "Ooze")
			{}
		};

		class MegaOoze : public Enemy
		{
		public:
			MegaOoze()
				:Enemy(64, 64, 400.0f, 0.4f, "Mega Ooze")
			{}
		};

		class DoubleOoze : public Enemy
		{
		public:
			DoubleOoze()
				:Enemy(48, 48, 10.0f, 0.5f, "Double Ooze")
			{}

		private:
			void Destroy() override;
		};

		class JumpingOoze : public Enemy
		{
		public:
			JumpingOoze()
				:Enemy(32, 32, 20.0f, 0.5f, "Jumping Ooze"), m_JumpTime(40), m_TimeBetweenJumps(180), m_JumpCoolDown(m_TimeBetweenJumps),
				m_JumpFrame(m_JumpTime+1), m_JumpDistance(80), m_JumpGoal()
			{}

		private:
			void Move() override;
			Vec2 FindJumpDestination();

			int m_JumpTime, m_TimeBetweenJumps, m_JumpCoolDown, m_JumpFrame, m_JumpDistance;
			Vec2 m_JumpGoal, m_JumpStart;
		};

		class Doubler : public Enemy
		{
		public:
			Doubler()
				:Enemy(32, 32, 20.0f, 0.3f, "Doubler"), m_GrowTime(40), m_Time(0)
			{}

		private:
			void Update() override;
			void Split();

			int m_GrowTime, m_Time;
		};

		class ShieldRat : public Enemy
		{
		public:
			ShieldRat()
				:Enemy(32, 32, 40.0f, 0.5f, "Shield Rat")
			{
				m_Armor = 100;
			}

		private:
			void TakeDamage(float damage, unsigned int source, Tower::DamageType type) override;
		};
	}
}