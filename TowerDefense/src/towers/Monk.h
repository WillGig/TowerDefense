#pragma once
#include "Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Monk : public Tower
		{
		public:
			Monk(bool upgraded);
			void Update() override;
			void EndRound() override;

			inline int GetNumberOfFocus() const { return m_NumberOfFocus; }
			inline void SetNumberOfFocus(int num) { m_NumberOfFocus = num; }

			std::shared_ptr<Tower> Clone();

		private:
			void Clicked() override;
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;
			virtual std::shared_ptr<Upgrade> GetRandomTowerUpgrade(std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> exclude) override;

			bool m_Upgraded, m_Focused;
			int m_NumberOfFocus;

			std::shared_ptr<Image> m_FocusedImage;
		};
	}
}