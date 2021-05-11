#include "pch.h"
#include "BuildButton.h"

TowerDefense::BuildButton::BuildButton(const std::string& button, Vec4i cost, std::shared_ptr<BaseScene> scene)
	:m_Button(std::make_unique<Button>(0.0f, 0.0f, 190, 33, button)), m_Cost(cost), m_Scene(scene),
	m_WoodCost(std::make_unique<Text>(std::to_string(cost.w), 0.0f, 0.0f, 12.0f, 0.0f)),
	m_StoneCost(std::make_unique<Text>(std::to_string(cost.x), 0.0f, 0.0f, 12.0f, 0.0f)),
	m_WheatCost(std::make_unique<Text>(std::to_string(cost.y), 0.0f, 0.0f, 12.0f, 0.0f)),
	m_WoodImage(std::make_unique<Image>("woodIcon", 0.0f, 0.0f, 24, 24, 0.0f)),
	m_StoneImage(std::make_unique<Image>("stoneIcon", 0.0f, 0.0f, 24, 24, 0.0f)),
	m_WheatImage(std::make_unique<Image>("wheatIcon", 0.0f, 0.0f, 24, 24, 0.0f))
{
	m_WoodCost->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_StoneCost->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_WheatCost->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::BuildButton::Render()
{
	m_Button->Render();
	m_WoodCost->Render();
	m_StoneCost->Render();
	m_WheatCost->Render();
	m_WoodImage->Render();
	m_StoneImage->Render();
	m_WheatImage->Render();
}

void TowerDefense::BuildButton::Update()
{
	m_Button->Update();
}

void TowerDefense::BuildButton::SetPosition(float x, float y)
{
	m_Button->SetX(x - 50);
	m_Button->SetY(y);
	m_WoodCost->SetPosition(x + 100, y, 0.0f);
	m_WoodImage->SetPosition(x + 130, y, 0.0f);
	m_StoneCost->SetPosition(x + 175, y, 0.0f);
	m_StoneImage->SetPosition(x + 205, y, 0.0f);
	m_WheatCost->SetPosition(x + 250, y, 0.0f);
	m_WheatImage->SetPosition(x + 280, y, 0.0f);
}