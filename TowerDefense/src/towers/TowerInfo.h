#pragma once

namespace TowerDefense
{
	class TowerInfo : public Entity
	{
	public:
		TowerInfo(float x, float y);
		void Update() override;

		inline bool Dragging() { return m_Dragging; }

	private:
		bool m_Dragging;
		float m_PreviousMouseX, m_PreviousMouseY;
	};
}