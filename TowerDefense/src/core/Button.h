#pragma once
#include "Entity.h"

namespace TowerDefense
{
	class Button : public Entity
	{
	public:
		Button(float x, float y, int width, int height, const std::string& image);
		void Update() override;

		inline bool IsSelected() const { return m_Selected;  }
		void SetSelected(bool selected);

		inline bool IsClicked() const { return m_Clicked; }
		
		void SetImages(const std::string& image);

	private:
		bool m_Selected, m_Clicked;
		std::shared_ptr<Image> m_RegularImage, m_SelectedImage;
	};
}