#pragma once

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void Bind() const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	static std::shared_ptr<Texture> GetTexture(const std::string& name);
	static void LoadTexture(const std::string& path);
	static void FreeTextures();

private:
	unsigned int m_RendererID;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

	static std::unique_ptr<std::unordered_map<std::string, std::shared_ptr<Texture>>> s_TextureCache;
};