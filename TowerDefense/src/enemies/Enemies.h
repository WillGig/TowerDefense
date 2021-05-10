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
				m_Damage = 20;
			}
		};

		class Goblin : public Enemy
		{
		public:
			Goblin()
				:Enemy(32, 32, 30.0f, 1.0f, "Goblin")
			{}
		};

		class Orc : public Enemy
		{
		public:
			Orc()
				:Enemy(32, 32, 80.0f, 0.8f, "Orc ")
			{}
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
	}
}