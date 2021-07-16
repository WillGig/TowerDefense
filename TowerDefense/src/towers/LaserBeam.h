#pragma once
#include "enemies/Enemy.h"

namespace TowerDefense
{
	class LaserBeam : public Entity
	{
	public:
		LaserBeam(std::shared_ptr<Entity> m_Source, std::shared_ptr<Enemy::Enemy> m_Target);
		void Update() override;
		void Render() override;

	private:
		Line m_Line;
		Circle m_Circle;

		float m_CircleRadius, m_CircleChange;

		std::shared_ptr<Entity> m_Source;
		std::shared_ptr<Enemy::Enemy> m_Target;
	};
}