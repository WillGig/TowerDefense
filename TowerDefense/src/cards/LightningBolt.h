#pragma once

namespace TowerDefense
{
	class LightningBolt : public Entity
	{
	public:
		LightningBolt(float startX, float startY, float endX, float endY);
		void Render() override;
		void Update() override;

	private:
		std::vector<Line> GenerateBolt(float startX, float startY, float endX, float endY);

		std::unique_ptr<std::vector<Line>> m_Bolt;
	};
}