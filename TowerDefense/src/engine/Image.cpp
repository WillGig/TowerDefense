#include "pch.h"
#include "Image.h"
#include "TowerDefense.h"

Image::Image(const std::string& file, float x, float y, int width, int height, float rotation)
	: m_Width(width), m_Height(height), m_Rotation(rotation), 
	m_Position(x, y, 0), m_File(file)
{
	float positions[] = {
			-width / 2.0f, -height / 2.0f, 0.0f, 0.0f,
			 width / 2.0f, -height / 2.0f, 1.0f, 0.0f,
			 width / 2.0f,  height / 2.0f, 1.0f, 1.0f,
			-width / 2.0f,  height / 2.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float), false);
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);

	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

	m_Shader = Shader::GetShader("res/shaders/Texture.Shader");
	m_Shader->Bind();
	m_Texture = Texture::GetTexture(file);
	m_Shader->SetUniform1i("u_Texture", 0);
}

void Image::Render()
{
	m_Texture->Bind();
	{
		Mat4f model = Mat4f::Translate(m_Position) * Mat4f::Rotate(m_Rotation);
		Mat4f mvp = Renderer::Get().GetProjectionMatrix() * model;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		Renderer::Get().Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}
}
