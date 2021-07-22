#pragma once

namespace TowerDefense
{
	class RangeBuff : public Buff
	{
	public:
		RangeBuff(int duration, int source, int modifier);
		void Apply(Tower::Tower& t) override;
		void Remove(Tower::Tower& t) override;

	private:
		int m_Modifier;
	};
}