#pragma once
#include "Renderer.h"


class Image
{
public:
	Image(const std::string& file, float x, float y, int width, int height, float rotation);
	void Render();
	inline Vec3 GetPosition() const { return m_Position; }
	inline void SetPosition(Vec3& newPosition) { m_Position = newPosition; }
	inline void SetPosition(float x, float y, float z) { m_Position.x = x; m_Position.y = y; m_Position.z = z; }
	inline void SetRotation(float rotation) { m_Rotation = rotation; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline float GetRotation() const { return m_Rotation; }
	inline std::string GetFile() const { return m_File; }
private:
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<Texture> m_Texture;

	int m_Width, m_Height;

	//Rotation in degrees
	float m_Rotation;

	//position of center of rectangle. Scale is relative to Renderer projection matrix
	Vec3 m_Position;
	std::string m_File;
};
