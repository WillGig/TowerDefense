#pragma once

class Text
{
public:
	//maxWidth is the maximum size of a line before text wrapping. Can be set to 0 or -1 for no wrapping.
	Text(std::string msg, float x, float y, float size, float maxWidth);

	void Render();

	Vec3 GetPosition() const { return m_Position; };

	inline void SetPosition(Vec3& newPosition) { m_Position = newPosition; }

	inline void SetPosition(float v1, float v2, float v3) { m_Position.x = v1; m_Position.y = v2, m_Position.z = v3; }

	inline void SetRotation(float rot) { m_Rotation = rot; }

	void SetColor(float r, float g, float b, float a);

	inline std::string GetMessage() { return m_Message; }

private:
	std::unique_ptr<float[]> GetPositions(char c, int xOff, int yOff, float scale);
	std::pair<int, int> GetMessageSize(const std::string& msg, float size, float maxWidth);

	float GetWidth(char c) const;

	std::pair<float, float> GetCoords(char c);

private:
	std::string m_Message;
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
	std::unique_ptr<Shader> m_Shader;
	std::shared_ptr<Texture> m_Texture;

	//position of center of rectangle. Scale is relative to Renderer projection matrix
	Vec3 m_Position;

	//Color using floats from 0.0f to 1.0f in rgba format
	Vec4 m_Color;

	float m_Rotation;
};