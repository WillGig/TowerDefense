#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
    Renderer(const Renderer&) = delete;
    static Renderer& Get();

    inline Mat4f GetProjectionMatrix() { return m_Proj; }

    void SetProjectionMatrix(float left, float right, float bottom, float top, float near, float far);

    void Clear() const;

    //Sets background clear color using floats from 0.0f to 1.0f
    void Clear(float r, float g, float b, float a) const;

    //Draws vertex and index data using shader
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

    //Draw line with vertex data using shader
    void Draw(const VertexArray& va, const Shader& shader) const;

private:
    Renderer();

    //Projection matrix based on Game Width and Height
    Mat4f m_Proj;
};