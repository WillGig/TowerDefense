#pragma once

namespace TowerDefense
{
	class SpeedBuff : public Buff
	{
	public:
		SpeedBuff(int duration, int source, float modifier);
		void Apply(Tower::Tower& t) override;
		void Remove(Tower::Tower& t) override;

	private:
		float m_Modifier;
	};
}