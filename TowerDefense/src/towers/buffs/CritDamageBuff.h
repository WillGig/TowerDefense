#pragma once

namespace TowerDefense
{
	class CritDamageBuff : public Buff
	{
	public:
		CritDamageBuff(int duration, int source, float modifier);
		void Apply(Tower::Tower& t) override;
		void Remove(Tower::Tower& t) override;

	private:
		float m_Modifier;
	};
}