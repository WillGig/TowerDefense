#include "pch.h"
#include "Animation.h"
#include "Renderer.h"
#include "TowerDefense.h"

Animation::Animation(const std::string& file, float x, float y, int width, int height, float rotation, int numFrames)
	: m_Width(width), m_Height(height), m_NumberOfFrames(numFrames), m_Rotation(rotation),
	m_Position(x, y, 0), m_File(file)
{

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, 4 * 4 * sizeof(float), true);
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);

	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

	m_Shader = std::make_unique<Shader>("res/shaders/Texture.Shader");
	m_Shader->Bind();
	m_Texture = std::make_unique<Texture>(file);
	m_Shader->SetUniform1i("u_Texture", 0);

	SetFrame(0);
}

void Animation::Render()
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

void Animation::SetFrame(int frame)
{
	float startX = (1.0f / m_NumberOfFrames) * frame;
	float endX = startX + (1.0f / m_NumberOfFrames);

	float positions[] = {
		-m_Width / 2.0f, -m_Height / 2.0f, startX, 0.0f,
		 m_Width / 2.0f, -m_Height / 2.0f, endX, 0.0f,
		 m_Width / 2.0f,  m_Height / 2.0f, endX, 1.0f,
		-m_Width / 2.0f,  m_Height / 2.0f, startX, 1.0f
	};

	m_VertexBuffer->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
}
