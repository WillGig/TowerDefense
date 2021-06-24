#pragma once

namespace TowerDefense
{
	class HealthBar
	{
	public:
		HealthBar(float x, float y, float width, float height);
		void Render();
		void SetFill(float percent, float poisonPercent);
		void SetPosition(float x, float y);
		inline float GetBarWidth() const { return m_Image->GetWidth() + m_PoisonBar->GetWidth(); }

	private:
		float m_X, m_Y, m_Width, m_Height;
		std::unique_ptr<Rectangle> m_Image, m_PoisonBar;
	};
}