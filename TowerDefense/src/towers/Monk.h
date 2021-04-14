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
			std::shared_ptr<Tower> Clone();

		protected:
			void Clicked() override;
			void Fire(std::shared_ptr<TowerDefense::Entity> target) override;

		private:
			bool m_Upgraded, m_Focused;

			std::shared_ptr<Image> m_FocusedImage;
		};
	}
}