#include "pch.h"
#include "Tile.h"

TowerDefense::Tile::Tile(float x, float y, int width, int height, int texture)
	:m_X(x), m_Y(y), m_Width(width), m_Height(height), m_Texture(texture), 
	m_Occupied(false), m_ContainedObject()
{

}

void TowerDefense::Tile::SetContainedObject(std::shared_ptr<Entity> object)
{ 
	m_ContainedObject = object; 
	if (!object) 
		m_Occupied = false; 
}

bool TowerDefense::Tile::Contains(float x, float y) const
{
	return !(x < m_X - m_Width / 2 || x > m_X + m_Width / 2 || y < m_Y - m_Height / 2 || y > m_Y + m_Height / 2);
}
