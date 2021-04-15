#pragma once
#include "Entity.h"

namespace TowerDefense {
	class AnimationEffect : public Entity
	{
	public:
		AnimationEffect(float x, float y, int width, int height, const std::string& animation, int numFrames, int duration);
		void Render() override;
		void Update() override;
		void Destroy();

	private:
		int m_Frame, m_Duration, m_LifeTime;
		std::unique_ptr<Animation> m_Animation;
	};
}
