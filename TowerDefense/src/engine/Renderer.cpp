#include "pch.h"
#include "TowerDefense.h"

Renderer& Renderer::Get()
{
    static Renderer instance;
    return instance;
}

Renderer::Renderer()
    :m_Proj(Mat4f::Orthographic(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f))
{
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::SetProjectionMatrix(float left, float right, float bottom, float top, float near, float far)
{
    m_Proj = Mat4f::Orthographic(left, right, bottom, top, near, far);
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

//Sets background clear color using floats from 0.0f to 1.0f
void Renderer::Clear(float r, float g, float b, float a) const
{
    GLCall(glClearColor(r, g, b, a));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const VertexArray& va, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    GLCall(glDrawArrays(GL_LINES, 0, 2));
}