#pragma once
#include "Enemy.h"

namespace TowerDefense
{
	class EnemyIcon
	{
	public:
		EnemyIcon(std::shared_ptr<Enemy::Enemy> enemy);
		void Render();
		void Update();

		void SetPosition(float x, float y);

		inline std::string GetName() const { return m_Name; }

	private:
		std::string m_Name;
		std::unique_ptr<Image> m_Image;
		std::unique_ptr<Text> m_NameText;
	};
}