#include "pch.h"
#include "Rectangle.h"

Rectangle::Rectangle(float x, float y, float width, float height)
	: m_Color(1.0f, 1.0f, 1.0f, 1.0f),
	m_Position(x, y, 0.0f), m_Width(width), m_Height(height)
{
	float positions[] = {
			-width/2, -height/2,
			 width/2, -height/2,
			 width/2,  height/2,
			-width/2,  height/2,
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 2 * sizeof(float), false);
	VertexBufferLayout layout;
	layout.Push<float>(2);

	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

	m_Shader = Shader::GetShader("res/shaders/Rectangle.Shader");
	m_Shader->Bind();
}

void Rectangle::Render()
{
	Mat4f mvp = Renderer::Get().GetProjectionMatrix() * Mat4f::Translate(m_Position);
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_MVP", mvp);
	m_Shader->SetUniform4f("u_Color", m_Color.w, m_Color.x, m_Color.y, m_Color.z);
	Renderer::Get().Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
}