#pragma once
#include "Projectile.h"

namespace TowerDefense
{
	class Arrow : public Projectile
	{
	public:
		Arrow(float x, float y, float direction, float damage, float armorReduction, unsigned int source)
			:Projectile(x, y, 6, 12, 8, direction, 300, damage, "projectiles/arrow", source), 
			m_ArmorReduction(armorReduction)
		{}

	private:
		void HitEntity(std::shared_ptr<Entity> e) override;
		
		float m_ArmorReduction;
	};

	class MagicMissile : public Projectile
	{
	public:
		MagicMissile(float x, float y, float direction, float damage, unsigned int source)
			:Projectile(x, y, 8, 8, 2, direction, 500, damage, "projectiles/magicMissile", source)
		{
			m_TurnSpeed = 2.0f;
		}

	protected:
		void HitEntity(std::shared_ptr<Entity> e) override;
	};

	class GraveBolt : public Projectile
	{
	public:
		GraveBolt(float x, float y, float direction, float damage, unsigned int source)
			:Projectile(x, y, 12, 12, 1.7f, direction, 500, damage, "projectiles/graveBolt", source)
		{
			m_TurnSpeed = 2.0f;
		}

	protected:
		void HitEntity(std::shared_ptr<Entity> e) override;
	};

	class GiantRock : public Projectile
	{
	public:
		GiantRock(float x, float y, float direction, float damage, unsigned int source)
			:Projectile(x, y, 32, 32, 4, direction, 300, damage, "projectiles/giantRock", source), m_Health(5),
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
		PoisonBomb(float x, float y, float direction, float damage, unsigned int source)
			:Projectile(x, y, 12, 12, 4, direction, 200, damage, "projectiles/poisonBomb", source),
			m_Radius(50), m_PoisonTime(240)
		{
		}

	protected:
		void HitEntity(std::shared_ptr<Entity> e) override;

	private:
		int m_Radius, m_PoisonTime;
	};
}