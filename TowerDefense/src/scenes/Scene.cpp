#include "pch.h"
#include "Scene.h"

std::unique_ptr<Rectangle> TowerDefense::Scene::s_Fade;

void TowerDefense::Scene::RenderFade(float alpha)
{
	s_Fade->SetColor(0.0f, 0.0f, 0.0f, alpha);
	s_Fade->Render();
}

void TowerDefense::Scene::Init()
{
	s_Fade = std::make_unique<Rectangle>(400.0f, 300.0f, 800.0f, 600.0f);
}

void TowerDefense::Scene::CleanUp()
{
	s_Fade.reset();
}