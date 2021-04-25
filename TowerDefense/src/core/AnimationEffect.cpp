#include "pch.h"
#include "AnimationEffect.h"
#include "scenes/Combat.h"

TowerDefense::AnimationEffect::AnimationEffect(float x, float y, int width, int height, const std::string& animation, int numFrames, int duration)
	:Entity(x, y, width, height, 0.0f, animation, Type::ANIMATION), m_Frame(0), m_Duration(duration), m_LifeTime(0),
	m_Animation(std::make_unique<Animation>(animation, x, y, width, height, 0.0f, numFrames))
{
}

void TowerDefense::AnimationEffect::Render()
{
	m_Animation->Render();
}

void TowerDefense::AnimationEffect::Update()
{
	m_LifeTime += Combat::GetRoundSpeed();
	if (m_LifeTime > m_Duration)
	{
		Destroy();
		return;
	}

	if ((float)m_LifeTime/ (float)m_Duration > (float)m_Frame/ (float)m_Animation->GetNumberOfFrames())
	{
		m_Frame++;
		if (m_Frame < m_Animation->GetNumberOfFrames())
			m_Animation->SetFrame(m_Frame);
	}
}

void TowerDefense::AnimationEffect::Destroy()
{
	Combat::RemoveEntity(m_ID);
}