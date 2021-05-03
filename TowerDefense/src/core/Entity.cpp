#include "pch.h"
#include "Entity.h"

unsigned int TowerDefense::Entity::s_ID = 0;

TowerDefense::Entity::Entity(float x, float y, int width, int height, float rotation, const std::string& image, Type type)
	:m_ID(s_ID), m_EntityType(type), m_Width(width), m_Height(height), m_X(x), m_Y(y), m_Rotation(rotation)
{
	if(image != "")
		m_Image = std::make_shared<Image>(image, x, y, width, height, rotation);
	s_ID++;
}

void TowerDefense::Entity::Render()
{
	m_Image->Render();
}

void TowerDefense::Entity::EndRound()
{

}

//Simple rectangular hitbox by default
bool TowerDefense::Entity::Contains(float x, float y) const
{
	return !(x < m_X - m_Width/2 || x > m_X + m_Width/2 || y < m_Y - m_Height/2 || y > m_Y + m_Height/2);
}

float TowerDefense::Entity::GetDistance(float x, float y) const
{
	return (float)sqrt(pow(m_X - x, 2) + pow(m_Y - y, 2.0));
}

void TowerDefense::Entity::SetImage(std::shared_ptr<Image> image) 
{ 
	if (m_Image->GetWidth() != image->GetWidth())
	{
		m_Image = std::make_shared<Image>(image->GetFile(), m_X, m_Y, m_Width, m_Height, m_Rotation);
		return;
	}

	image->SetPosition(m_Image->GetPosition().x, m_Image->GetPosition().y, m_Image->GetPosition().z);
	image->SetRotation(m_Image->GetRotation());
	m_Image = image; 
}