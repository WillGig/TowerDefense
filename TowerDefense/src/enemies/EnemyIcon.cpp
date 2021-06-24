#include "pch.h"
#include "EnemyIcon.h"

TowerDefense::EnemyIcon::EnemyIcon(std::shared_ptr<Enemy::Enemy> enemy)
	:m_Name(enemy->GetName()), 
	m_Image(std::make_unique<Image>(m_Name, 0.0f, 0.0f, enemy->GetWidth()*2, enemy->GetHeight()*2, 90.0f)),
	m_NameText(std::make_unique<Text>(m_Name, 0.0f, 0.0f, 10.0f, 0.0f))
{
	m_NameText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::EnemyIcon::Render()
{
	m_Image->Render();
	m_NameText->Render();
}

void TowerDefense::EnemyIcon::Update()
{

}

void TowerDefense::EnemyIcon::SetPosition(float x, float y)
{
	m_Image->SetPosition(x, y, 0.0f);
	m_NameText->SetPosition(x, y - m_Image->GetHeight()/2 - 10.0f, 0.0f);
}