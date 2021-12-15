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

		inline bool RequiresFocus() const { return m_RequiresFocus; }

		inline virtual bool ValueChanged() { return false; }

		inline int GetValue() { return m_Value; }

		inline virtual void SetValue(int value) { m_Value = value; }
		
		void SetImages(const std::string& image);

		inline std::string GetImageName() const { return m_RegularImage->GetFile(); }

	private:
		bool m_Selected, m_Clicked;
		std::shared_ptr<Image> m_RegularImage, m_SelectedImage;

	protected:

		int m_Value;

		bool m_RequiresFocus;
	};
}