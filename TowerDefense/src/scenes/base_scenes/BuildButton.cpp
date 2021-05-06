#include "pch.h"
#include "BuildButton.h"

TowerDefense::BuildButton::BuildButton(const std::string& button, int cost, std::shared_ptr<BaseScene> scene)
	:m_Button(std::make_unique<Button>(0.0f, 0.0f, 190, 33, button)), m_Cost(cost), m_Scene(scene),
	m_Text(std::make_unique<Text>(std::to_string(cost), 0.0f, 0.0f, 12.0f, 0.0f)),
	m_CoinImage(std::make_unique<Image>("goldIcon", 0.0f, 0.0f, 24, 24, 0.0f))
{
	m_Text->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::BuildButton::Render()
{
	m_Button->Render();
	m_Text->Render();
	m_CoinImage->Render();
}

void TowerDefense::BuildButton::Update()
{
	m_Button->Update();
}

void TowerDefense::BuildButton::SetPosition(float x, float y)
{
	m_Button->SetX(x - 50);
	m_Button->SetY(y);
	m_Text->SetPosition(x + 100, y + 2, 0.0f);
	m_CoinImage->SetPosition(x + 150, y, 0.0f);
}