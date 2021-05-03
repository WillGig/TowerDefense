#pragma once

class Line
{
public:
	Line(float startX, float startY, float endX, float endY);
	void Render();
	inline void SetThickness(float thickness) { m_Thickness = thickness; }
	inline Vec4 GetColor() const { return m_Color; };
	inline void SetColor(float r, float g, float b, float a) { m_Color = Vec4(r, g, b, a); }
private:
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Shader> m_Shader;

	float m_Thickness;

	//Color using floats from 0.0f to 1.0f in rgba format
	Vec4 m_Color;
};