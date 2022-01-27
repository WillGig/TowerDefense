#pragma once
#include "Enemy.h"

namespace TowerDefense
{
	namespace Enemy
	{
		enum t {
			//Rats
			RAT, GIANTRAT, SHIELDRAT, SHAMANRAT, HEALERRAT, PLAGUERAT, WITCHRAT, ASSASSINRAT, BOSSRAT,
			//Slimes
			SLIME, BLOB, OOZE, DOUBLEOOZE, MEGAOOZE, JUMPINGOOZE, DOUBLER, TOXICSLIME, WRITHINGMASS,
			//Bugs
			BEETLE, SPIDER, TOUGHBEETLE, BLINKBUG, RUNNERBEETLE, TANKBEETLE, GNAT, ANKHEG,
			//Other
			GOBLIN, ORC
		};

		class Rat : public Enemy
		{
		public:
			Rat()
				:Enemy(32, 32, 5.0f, 1.0f, 5, "Rat", 1)
			{}
		};

		class GiantRat : public Enemy
		{
		public:
			GiantRat()
				:Enemy(32, 32, 25.0f, 0.75f, 10, "Giant Rat", 3)
			{}
		};

		class BossRat : public Enemy
		{
		public:
			BossRat()
				:Enemy(64, 64, 250.0f, 0.3f, 100, "Boss Rat", 20)
			{
				m_Armor = 100;
				m_MagicResistance = 100;
			}
		};

		class Goblin : public Enemy
		{
		public:
			Goblin()
				:Enemy(32, 32, 13.0f, 1.0f, 10, "Goblin", 3)
			{
				m_Armor = 20;
				m_MagicResistance = 20;
			}
		};

		class Orc : public Enemy
		{
		public:
			Orc()
				:Enemy(32, 32, 25.0f, 0.8f, 20, "Orc ", 5)
			{
				m_Armor = 50;
				m_MagicResistance = 50;
			}
		};

		class Beetle : public Enemy
		{
		public:
			Beetle()
				:Enemy(32, 32, 2.0f, 2.0f, 2, "Beetle", 1)
			{}
		};

		class Slime : public Enemy
		{
		public:
			Slime()
				:Enemy(32, 32, 7.0f, 0.7f, 8, "Slime", 1)
			{}
		};

		class Spider : public Enemy
		{
		public:
			Spider()
				:Enemy(32, 32, 10.0f, 1.0f, 10, "Spider", 2)
			{}
		};

		class ToughBeetle : public Enemy
		{
		public:
			ToughBeetle()
				:Enemy(32, 32, 20.0f, 0.5f, 20, "Tough Beetle", 3)
			{
				m_Armor = 100;
			}
		};

		class Blob : public Enemy
		{
		public:
			Blob()
				:Enemy(32, 32, 14.0f, 0.65f, 8, "Blob", 3)
			{}

		private:
			void Destroy() override;
		};

		class Ooze : public Enemy
		{
		public:
			Ooze()
				:Enemy(32, 32, 28.0f, 0.6f, 8, "Ooze", 3)
			{}

		private:
			void Destroy() override;
		};

		class DoubleOoze : public Enemy
		{
		public:
			DoubleOoze()
				:Enemy(48, 48, 50.0f, 0.5f, 10, "Double Ooze", 3)
			{}

		private:
			void Destroy() override;
		};

		class MegaOoze : public Enemy
		{
		public:
			MegaOoze()
				:Enemy(64, 64, 100.0f, 0.4f, 50, "Mega Ooze", 10)
			{}

		private:
			void Destroy() override;
		};

		class JumpingOoze : public Enemy
		{
		public:
			JumpingOoze()
				:Enemy(32, 32, 10.0f, 0.5f, 15, "Jumping Ooze", 1), m_JumpTime(40), m_TimeBetweenJumps(180), m_JumpCoolDown(m_TimeBetweenJumps),
				m_JumpFrame(m_JumpTime + 1), m_JumpDistance(80), m_JumpGoal()
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
				:Enemy(32, 32, 20.0f, 0.3f, 0, "Doubler", 2), m_GrowTime(30), m_Time(0)
			{
				m_MaxHealth = 40;
			}

		private:
			void Update() override;
			void Split();

			int m_GrowTime, m_Time;
		};

		class ShieldRat : public Enemy
		{
		public:
			ShieldRat()
				:Enemy(32, 32, 20.0f, 0.5f, 20, "Shield Rat", 3)
			{
				m_Armor = 100;
			}

		private:
			void TakeDamage(float damage, unsigned int source, Tower::DamageType type) override;
			void DropShield();
		};

		class ShamanRat : public Enemy
		{
		public:
			ShamanRat()
				:Enemy(32, 32, 20.0f, 0.5f, 10, "Shaman Rat", 2), m_CastTime(180), m_Cast(0)
			{}
		private:
			void Update() override;
			void Cast();
			int m_CastTime, m_Cast;
		};

		class HealerRat : public Enemy
		{
		public:
			HealerRat()
				:Enemy(32, 32, 20.0f, 0.5f, 10, "Healer Rat", 2), m_CastTime(180), m_Cast(0)
			{}
		private:
			void Update() override;
			void Cast();
			int m_CastTime, m_Cast;
		};

		class BlinkBug : public Enemy
		{
		public:
			BlinkBug()
				:Enemy(32, 32, 10.0f, 0.7f, 10, "Blink Bug", 1), m_CastTime(180), m_Cast(0), m_InvisibleTime(180)
			{}
		private:
			void Update() override;
			int m_CastTime, m_Cast, m_InvisibleTime;
		};

		class RunnerBeetle : public Enemy
		{
		public:
			RunnerBeetle()
				:Enemy(32, 32, 25.0f, 0.4f, 10, "Runner Beetle", 2), m_CastTime(180), m_Cast(0), m_RunTime(60), m_Run(0)
			{
				m_Armor = 30;
			}
		private:
			void Move() override;
			int m_CastTime, m_Cast, m_RunTime, m_Run;
		};

		class TankBeetle : public Enemy
		{
		public:
			TankBeetle()
				:Enemy(64, 64, 300.0f, 0.25f, 100, "Tank Beetle", 20), m_SwitchTime(240), m_Switch(0)
			{
				m_Armor = 200;
			}
		private:
			void Update() override;
			int m_SwitchTime, m_Switch;
		};

		class PlagueRat : public Enemy
		{
		public:
			PlagueRat()
				:Enemy(32, 32, 10.0f, 1.5f, 20, "Plague Rat", 3)
			{}

		private:
			void Destroy() override;
		};

		class WitchRat : public Enemy
		{
		public:
			WitchRat()
				:Enemy(32, 32, 60.0f, 0.75f, 50, "Witch Rat", 5), m_CastTime(240), m_Cast(0)
			{}

		private:
			void Update() override;

			int m_CastTime, m_Cast;
		};

		class AssassinRat : public Enemy
		{
		public:
			AssassinRat()
				:Enemy(32, 32, 75.0f, 0.5f, 25, "Assassin Rat", 5), m_CastTime(180), m_Cast(0), m_Running(false), m_InvisibleTime(180)
			{
				m_Armor = 25;
				m_MagicResistance = 25;
			}
		private:
			void Update() override;
			void Move() override;
			bool m_Running;
			int m_CastTime, m_Cast, m_InvisibleTime;
		};

		class WrithingMass : public Enemy
		{
		public:
			WrithingMass()
				:Enemy(64, 64, 1000.0f, 0.15f, 200, "Writhing Mass", 50), m_Cast(0), m_CastTime(90)
			{
				m_Armor = 150;
				m_MagicResistance = 150;
			}

		private:
			void Update() override;
			void SummonSpawn();
			int m_CastTime, m_Cast;
		};

		class ToxicSlime : public Enemy
		{
		public:
			ToxicSlime()
				:Enemy(32, 32, 20.0f, 1.0f, 15, "Toxic Slime", 3)
			{}
		private:
			void Destroy() override;
		};

		class Gnat : public Enemy
		{
		public:
			Gnat()
				:Enemy(32, 32, 20.0f, 2.0f, 25, "Gnat", 7)
			{
				m_Visible = false;
			}
		};

		class Ankheg : public Enemy
		{
		public:
			Ankheg()
				:Enemy(32, 32, 300.0f, 0.7f, 50, "Ankheg", 10)
			{
				m_Armor = 100.0f;
				m_MagicResistance = 100.0f;
			}
		};

		class FireFly : public Enemy
		{
		public:
			FireFly()
				:Enemy(32, 32, 30.0f, 1.0f, 20, "Fire Fly", 5)
			{}
		private:
			void Destroy() override;
		};

		static std::shared_ptr<Enemy> GetEnemy(int type)
		{
			switch (type) {
			case RAT:
				return std::make_shared<Rat>();
			case GIANTRAT:
				return std::make_shared<GiantRat>();
			case GOBLIN:
				return std::make_shared<Goblin>();
			case ORC:
				return std::make_shared<Orc>();
			case BOSSRAT:
				return std::make_shared<BossRat>();
			case BEETLE:
				return std::make_shared<Beetle>();
			case SLIME:
				return std::make_shared<Slime>();
			case SPIDER:
				return std::make_shared<Spider>();
			case TOUGHBEETLE:
				return std::make_shared<ToughBeetle>();
			case GNAT:
				return std::make_shared<Gnat>();
			case BLOB:
				return std::make_shared<Blob>();
			case OOZE:
				return std::make_shared<Ooze>();
			case DOUBLEOOZE:
				return std::make_shared<DoubleOoze>();
			case MEGAOOZE:
				return std::make_shared<MegaOoze>();
			case JUMPINGOOZE:
				return std::make_shared<JumpingOoze>();
			case DOUBLER:
				return std::make_shared<Doubler>();
			case TOXICSLIME:
				return std::make_shared<ToxicSlime>();
			case SHIELDRAT:
				return std::make_shared<ShieldRat>();
			case SHAMANRAT:
				return std::make_shared<ShamanRat>();
			case HEALERRAT:
				return std::make_shared<HealerRat>();
			case BLINKBUG:
				return std::make_shared<BlinkBug>();
			case RUNNERBEETLE:
				return std::make_shared<RunnerBeetle>();
			case TANKBEETLE:
				return std::make_shared<TankBeetle>();
			case ANKHEG:
				return std::make_shared<Ankheg>();
			case PLAGUERAT:
				return std::make_shared<PlagueRat>();
			case WITCHRAT:
				return std::make_shared<WitchRat>();
			case ASSASSINRAT:
				return std::make_shared<AssassinRat>();
			case WRITHINGMASS:
				return std::make_shared<WrithingMass>();
			}
			return nullptr;
		}
	}
}