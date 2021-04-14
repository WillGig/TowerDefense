#include "pch.h"
#include "Circle.h"
#include "TowerDefense.h"

Circle::Circle(float x, float y, float radius)
	: m_Radius(radius), m_Thickness(3.0f), m_Color(1.0f, 1.0f, 1.0f, 1.0f), 
	m_Position(x, y, 0)
{
	float positions[] = {
			-radius, -radius, 0.0f, 0.0f,
			 radius, -radius, 1.0f, 0.0f,
			 radius,  radius, 1.0f, 1.0f,
			-radius,  radius, 0.0f, 1.0f
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

	m_Shader = std::make_unique<Shader>("res/shaders/Circle.Shader");
	m_Shader->Bind();
}

void Circle::Render()
{
	Mat4f mvp = Renderer::Get().GetProjectionMatrix() * Mat4f::Translate(m_Position);
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_MVP", mvp);
	m_Shader->SetUniform1f("u_Thickness", m_Thickness/m_Radius);
	m_Shader->SetUniform4f("u_Color", m_Color.w, m_Color.x, m_Color.y, m_Color.z);
	Renderer::Get().Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
}