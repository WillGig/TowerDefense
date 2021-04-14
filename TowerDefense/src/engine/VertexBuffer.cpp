#include "pch.h"

//Generate buffer with vertexdata. Size is size of data in bytes. Dynamic determines if vertex data will be changed dynamically
//data can be nullptr if dynamic is true
VertexBuffer::VertexBuffer(const void* data, unsigned int size, bool dynamic) 
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    if (dynamic)
    {
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    }   
    else
    {
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    } 
}

VertexBuffer::~VertexBuffer() 
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}