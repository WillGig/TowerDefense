#include "pch.h"
#include "Line.h"

Line::Line(Vec2 start, Vec2 end)
	:m_Thickness(3.0f), m_Color(1.0f, 1.0f, 1.0f, 1.0f)
{
	float positions[] = {
		start.x, start.y,
		end.x, end.y
	};
	m_Indices = 2;

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 2 * 2 * sizeof(float), false);
	VertexBufferLayout layout;
	layout.Push<float>(2);

	m_VAO->AddBuffer(*m_VertexBuffer, layout);

	m_Shader = Shader::GetShader("res/shaders/Line.Shader");
	m_Shader->Bind();
}

Line::Line(std::vector<Vec2> points)
	:m_Thickness(3.0f), m_Color(1.0f, 1.0f, 1.0f, 1.0f)
{
	m_Indices = points.size();

	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(points.data(), 2 * points.size() * sizeof(float), false);
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
	Renderer::Get().Draw(*m_VAO, *m_Shader, m_Indices);
}