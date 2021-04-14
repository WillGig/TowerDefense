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
				:Enemy(32, 32, 10.0f, 1.0f, "res/textures/rat.png", "res/textures/ratSelected.png")
			{}
		};

		class GiantRat : public Enemy
		{
		public:
			GiantRat()
				:Enemy(32, 32, 50.0f, 0.75f, "res/textures/giantRat.png", "res/textures/giantRatSelected.png")
			{}
		};

		class BossRat : public Enemy
		{
		public:
			BossRat()
				:Enemy(64, 64, 500.0f, 0.3f, "res/textures/bossRat.png", "res/textures/bossRatSelected.png")
			{
				m_Damage = 20;
			}
		};

		class Goblin : public Enemy
		{
		public:
			Goblin()
				:Enemy(32, 32, 30.0f, 1.0f, "res/textures/goblin.png", "res/textures/goblinSelected.png")
			{}
		};

		class Orc : public Enemy
		{
		public:
			Orc()
				:Enemy(32, 32, 60.0f, 0.8f, "res/textures/orc.png", "res/textures/orcSelected.png")
			{}
		};
	}
}