#pragma once
#include "Projectile.h"

namespace TowerDefense
{
	class Arrow : public Projectile
	{
	public:
		Arrow(float x, float y, float direction, float damage)
			:Projectile(x, y, 6, 12, 8, direction, 300, damage, "res/textures/arrow.png")
		{
		}

	protected:
		void HitEntity(std::shared_ptr<Entity> e) override;
	};

	class MagicMissile : public Projectile
	{
	public:
		MagicMissile(float x, float y, float direction, float damage)
			:Projectile(x, y, 8, 8, 2, direction, 500, damage, "res/textures/magicMissile.png")
		{
			m_TurnSpeed = 2.0f;
		}

	protected:
		void HitEntity(std::shared_ptr<Entity> e) override;
	};

	class GiantRock : public Projectile
	{
	public:
		GiantRock(float x, float y, float direction, float damage)
			:Projectile(x, y, 32, 32, 4, direction, 300, damage, "res/textures/giantRock.png"), m_Health(5),
			m_HitObjects(std::make_unique<std::array<int, 5>>())
		{
		}

	protected:
		void HitEntity(std::shared_ptr<Entity> e) override;

	private:
		int m_Health;
		std::unique_ptr<std::array<int, 5>> m_HitObjects;
	};

	class PoisonBomb : public Projectile
	{
	public:
		PoisonBomb(float x, float y, float direction, float damage)
			:Projectile(x, y, 12, 12, 4, direction, 200, damage, "res/textures/poisonBomb.png"),
			m_Radius(50), m_PoisonTime(240)
		{
		}

	protected:
		void HitEntity(std::shared_ptr<Entity> e) override;

	private:
		int m_Radius, m_PoisonTime;
	};
}