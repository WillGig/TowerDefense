#pragma once

class SpriteSheet
{
public:
	SpriteSheet(const std::string& file, int spriteWidth, int spriteHeight);
	~SpriteSheet();

	std::shared_ptr<Texture> load(int xOff, int yOff);

private:

	int m_Width, m_Height, m_BPP, m_SpriteWidth, m_SpriteHeight;

	unsigned char* m_LocalBuffer;
};