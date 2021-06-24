#pragma once

namespace TowerDefense
{
	class Artifact;

	class ArtifactSlot
	{
	public:
		ArtifactSlot(float x, float y, std::shared_ptr<Artifact> card, int price);
		void Render();
		void Update();
		inline bool ArtifactAvailable() { return m_Artifact != nullptr; };
		inline bool ShowingInfo() { return m_ShowingInfo; }

	private:
		int m_Price;
		bool m_ShowingInfo;

		std::shared_ptr<Artifact> m_Artifact;
		std::unique_ptr<Text> m_PriceText;
		std::unique_ptr<Image> m_GoldImage;
		std::unique_ptr<Rectangle> m_Fade;
	};
}