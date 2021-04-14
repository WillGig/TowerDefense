#pragma once

namespace TowerDefense
{
	class HealthBar
	{
	public:
		HealthBar(float x, float y, float width, float height);
		void Render();
		void SetFill(float percent);
		void SetColor(float r, float g, float b, float a);
		void SetPosition(float x, float y);

	private:
		float m_X, m_Y, m_Width, m_Height;
		Vec4 m_Color;
		std::unique_ptr<Rectangle> m_Image;
	};
}