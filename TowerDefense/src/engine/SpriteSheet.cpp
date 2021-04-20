#include "pch.h"
#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const std::string& file, int spriteWidth, int spriteHeight)
	:m_Width(0), m_Height(0), m_SpriteWidth(spriteWidth), m_SpriteHeight(spriteHeight), m_LocalBuffer(nullptr)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(file.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	if (!m_LocalBuffer)
		std::cout << "Failed to load spritesheet " << file << std::endl;
}

SpriteSheet::~SpriteSheet()
{
	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

//Loads in texture from spritesheet at specified coordinates
//Coordinates should be the sprites index on the sheet, NOT pixel coordinates
std::shared_ptr<Texture> SpriteSheet::load(int xOff, int yOff)
{
	yOff = m_Height / m_SpriteHeight - yOff - 1; //Invert y coordinate on sheet

	unsigned int spriteSize = m_SpriteWidth * m_SpriteHeight * 4;
	
	unsigned char* spriteBuffer = new unsigned char[spriteSize]();

	for (int y = 0; y < m_SpriteHeight; y++) {
		for (int x = 0; x < m_SpriteWidth; x++) {
			for (int i = 0; i < 4; i++)//4 Color Channels
			{
				spriteBuffer[(x + y * m_SpriteWidth) * 4 + i] = m_LocalBuffer[(x + xOff * m_SpriteWidth + (y + yOff * m_SpriteHeight) * m_Width) * 4 + i];
			}
		}
	}

	unsigned int rendererID = 0;

	GLCall(glGenTextures(1, &rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_SpriteWidth, m_SpriteHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, spriteBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	delete[] spriteBuffer;

	return std::make_shared<Texture>(rendererID, m_SpriteWidth, m_SpriteHeight, m_BPP);
}