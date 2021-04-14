#pragma once
#include "Entity.h"

namespace TowerDefense
{
	class Button : public Entity
	{
	public:
		Button(int width, int height, float x, float y, const std::string& image, const std::string& selectedImage);
		void Update() override;

		inline bool IsSelected() const { return m_Selected;  }
		void SetSelected(bool selected);

		inline bool IsClicked() const { return m_Clicked; }
		
		void SetImages(const std::string& image, const std::string& selectedImage);

	private:
		bool m_Selected, m_Clicked;
		std::shared_ptr<Image> m_RegularImage, m_SelectedImage;
	};
}