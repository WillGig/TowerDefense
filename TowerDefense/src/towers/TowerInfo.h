#pragma once
#include "Tower.h"

namespace TowerDefense
{
	class TowerInfo : public Entity
	{
	public:
		TowerInfo(float x, float y, std::shared_ptr<Tower::Tower> t);
		void Render() override;
		void Update() override;

		void SetX(float x) override;
		void SetY(float y) override;

		inline bool Dragging() { return m_Dragging; }

	private:
		bool m_Dragging;
		float m_PreviousMouseX, m_PreviousMouseY;

		std::unique_ptr<Text> m_Name;
		std::unique_ptr<Text> m_Stats;
	};
}