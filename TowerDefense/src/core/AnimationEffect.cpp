#include "pch.h"
#include "AnimationEffect.h"
#include "scenes/Combat.h"

TowerDefense::AnimationEffect::AnimationEffect(float x, float y, int width, int height, const std::string& animation, int numFrames)
	:Entity(width, height, x, y, 0.0f, animation, Type::ANIMATION), m_Frame(0), 
	m_Animation(std::make_unique<Animation>(animation, x, y, width, height, 0.0f, numFrames))
{
}

void TowerDefense::AnimationEffect::Render()
{
	m_Animation->Render();
}

void TowerDefense::AnimationEffect::Update()
{
	m_Frame++;
	if (m_Frame < m_Animation->GetNumberOfFrames()) 
		m_Animation->SetFrame(m_Frame);
	else 
		Destroy();
}

void TowerDefense::AnimationEffect::Destroy()
{
	Combat::RemoveEntity(m_ID);
}