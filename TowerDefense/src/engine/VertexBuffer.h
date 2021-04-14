#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;

public:
	//Generate buffer with vertexdata. Size is size of data in bytes. Dynamic determines if vertex data will be changed dynamically
	//data can be nullptr if dynamic is true
	VertexBuffer(const void* data, unsigned int size, bool dynamic);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};