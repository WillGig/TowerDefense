#pragma once
#include "enemies/Enemy.h"

namespace TowerDefense
{
	class Projectile : public Entity
	{
	public:
		Projectile(float x, float y, int width, int height, float speed, float rotation, float range, float damage, const std::string& image, unsigned int source);
		void Update() override;
		void Destroy();

		inline float GetTurnSpeed() const { return m_TurnSpeed; }
		inline void SetTurnSpeed(float num) { m_TurnSpeed = num; }

		inline float GetSpeed() const { return m_Speed; }
		inline void SetSpeed(float num) { m_Speed = num; }

	protected:
		virtual void HitEntity(std::shared_ptr<Entity> e) = 0;

		float m_TurnSpeed, m_Damage;

		unsigned int m_TowerSource;

	private:
		void UpdateDirection();
		void Move();
		void CheckCollisions();
		bool OffScreen();
		std::shared_ptr<Enemy::Enemy> FindTarget();

		float m_Speed, m_Range, m_DistanceTraveled;
		std::shared_ptr<Enemy::Enemy> m_Target;
	};


}