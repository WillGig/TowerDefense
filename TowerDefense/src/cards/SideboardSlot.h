#pragma once

namespace TowerDefense
{
	class Card;

	class SideboardSlot : public Entity
	{
	public:
		SideboardSlot();
		void Update() override;
		void Render() override;

		void Clear();

		inline unsigned int GetCard() { return m_Card; }
		inline bool SelectingCard() { return m_SelectingCard; }

	private:
		bool m_SelectingCard;

		unsigned int m_Card;
	};
}
