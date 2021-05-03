#include "pch.h"
#include "Line.h"

Line::Line(float startX, float startY, float endX, float endY)
	: m_Thickness(3.0f), m_Color(1.0f, 1.0f, 1.0f, 1.0f)
{
	float positions[] = {
		startX,	startY,
		endX,	endY
	};

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 2 * 2 * sizeof(float), false);
	VertexBufferLayout layout;
	layout.Push<float>(2);

	m_VAO->AddBuffer(*m_VertexBuffer, layout);

	m_Shader = Shader::GetShader("res/shaders/Line.Shader");
	m_Shader->Bind();
}

void Line::Render()
{
	Mat4f mvp = Renderer::Get().GetProjectionMatrix();
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_MVP", mvp);
	GLCall(glLineWidth(m_Thickness));
	m_Shader->SetUniform4f("u_Color", m_Color.w, m_Color.x, m_Color.y, m_Color.z);
	Renderer::Get().Draw(*m_VAO, *m_Shader);
}