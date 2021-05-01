#pragma once
#include "pch.h"

namespace TowerDefense
{
	class InfoTile
	{
	public:
		InfoTile(const std::string& image)
		{
			m_Image = std::make_unique<Image>(image, 0.0f, 0.0f, 220, 85, 0.0f);
		}

		inline void Render() { m_Image->Render(); }

		inline void SetPosition(float x, float y) { m_Image->SetPosition(x, y, 0.0f); }

	private:
		std::unique_ptr<Image> m_Image;
	};
}