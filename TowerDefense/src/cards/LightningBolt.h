#pragma once

namespace TowerDefense
{
	class LightningBolt : public Entity
	{
	public:
		LightningBolt(Vec2 start, Vec2 end);
		void Render() override;
		void Update() override;

	private:
		std::vector<Vec2> GenerateBolt(Vec2 start, Vec2 end);

		std::unique_ptr<Line> m_Bolt;
	};
}