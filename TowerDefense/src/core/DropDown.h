#pragma once


namespace TowerDefense
{

	class DropDown : public Button
	{
	public:
		DropDown(float x, float y, int width, int height, std::vector<std::string> images);
		void Render() override;
		void Update() override;

		void SetValue(int value) override;

		inline bool ValueChanged() override { return m_ValueChanged; m_ValueChanged = false; }

	private:

		bool m_ValueChanged;

		std::unique_ptr<std::vector<std::unique_ptr<Button>>> m_Buttons;
	};

}