#pragma once
#include "Entity.h"

namespace TowerDefense
{
	class StaticImage : public Entity
	{
	public:
		StaticImage(float x, float y, int width, int height, float rotation, const std::string& image)
			:Entity(x, y, width, height, rotation, image, Type::STATICIMAGE)
		{}
		void Update() override {}
	};
}