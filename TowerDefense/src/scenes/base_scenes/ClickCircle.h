#pragma once

namespace TowerDefense
{
	class ClickCircle : public Entity
	{
	public:
		ClickCircle(float x, float y, float radius, float changeSpeed);
		void Update() override;
		void Render() override;
		bool Contains(float x, float y) const override;

		inline bool Remove() { return m_Remove; }
		inline bool Clicked() { return m_Clicked; }

	private:
		float m_Radius, m_ChangeSpeed;

		bool m_Remove, m_Clicked;

		Circle m_CircleImage;
	};
}