#pragma once
#include "pch.h"

namespace TowerDefense
{
	class InfoTile
	{
	public:
		InfoTile(const std::string& image)
		{
			m_Image = std::make_unique<StaticImage>(0.0f, 0.0f, 220, 85, 0.0f, image);
		}

		inline void Render() { m_Image->Render(); }

		inline void SetPosition(float x, float y) { m_Image->SetX(x); m_Image->SetY(y); }

	private:
		std::unique_ptr<StaticImage> m_Image;
	};
}