#include "pch.h"
#include "Line.h"

Line::Line(float x, float y, float length, float rotation)
	: m_Length(length), m_Thickness(3.0f), m_Color(1.0f, 1.0f, 1.0f, 1.0f),
	m_Position(x, y, 0)
{
	float positions[] = {
			-length / 2, -0.0f,
			 length / 2, -0.0f,
			 length / 2,  0.0f,
			-length / 2,  0.0f,
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 2 * sizeof(float), false);
	VertexBufferLayout layout;
	layout.Push<float>(2);

	m_VAO->AddBuffer(*m_VertexBuffer, layout);

	m_Shader = Shader::GetShader("res/shaders/Line.Shader");
	m_Shader->Bind();
}

void Line::Render()
{
	Mat4f mvp = Renderer::Get().GetProjectionMatrix() * Mat4f::Translate(m_Position) * Mat4f::Rotate(m_Rotation);
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_MVP", mvp);
	GLCall(glLineWidth(m_Thickness));
	m_Shader->SetUniform4f("u_Color", m_Color.w, m_Color.x, m_Color.y, m_Color.z);
	Renderer::Get().Draw(*m_VAO, *m_Shader);
}