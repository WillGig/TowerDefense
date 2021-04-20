#include "pch.h"

std::unique_ptr<std::unordered_map<std::string, std::shared_ptr<Texture>>> Texture::s_TextureCache = std::make_unique<std::unordered_map<std::string, std::shared_ptr<Texture>>>();

//Load in png from path using stbi and store in m_Localbuffer
Texture::Texture(const std::string& path)
	:m_RendererID(0), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
	else
		std::cout << "Failed to load texture " << path << std::endl;
}

Texture::Texture(unsigned int rendererID, int width, int height, int BPP)
	:m_RendererID(rendererID), m_LocalBuffer(nullptr), m_Width(width), m_Height(height), m_BPP(BPP)
{
}


Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind() const
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

std::shared_ptr<Texture> Texture::GetTexture(const std::string& name)
{
	if (s_TextureCache->find(name) != s_TextureCache->end())
		return s_TextureCache->at(name);

	LoadTexture(name);
	if (s_TextureCache->find(name) != s_TextureCache->end())
		return s_TextureCache->at(name);

	std::cout << "Error: Failed to find texture: " << name << std::endl;
	return nullptr;
}

void Texture::LoadTexture(const std::string& path)
{
	s_TextureCache->insert({ path,  std::make_shared<Texture>("res/textures/" + path + ".png") });
}

void Texture::LoadTexture(const std::string& path, std::shared_ptr<Texture> tex)
{
	s_TextureCache->insert({ path,  tex });
}

void Texture::FreeTextures()
{
	s_TextureCache.reset();
}