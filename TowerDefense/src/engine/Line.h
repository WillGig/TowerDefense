#pragma once

class Line
{
public:
	Line(float x, float y, float length, float rotation);
	void Render();
	inline Vec3 GetPosition() const { return m_Position; }
	inline void SetPosition(Vec3& newPosition) { m_Position = newPosition; }
	inline void SetPosition(float x, float y, float z) { m_Position.x = x; m_Position.y = y; m_Position.z = z; }
	inline float GetRotation() const { return m_Rotation; }
	inline void SetRotation(float rot) { m_Rotation = rot; }
	inline void SetThickness(float thickness) { m_Thickness = thickness; }
	inline void SetColor(float r, float g, float b, float a) { m_Color = Vec4(r, g, b, a); }
private:
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Shader> m_Shader;

	float m_Length, m_Thickness, m_Rotation;

	//Color using floats from 0.0f to 1.0f in rgba format
	Vec4 m_Color;

	//position of center of line. Scale is relative to Renderer projection matrix
	Vec3 m_Position;
};