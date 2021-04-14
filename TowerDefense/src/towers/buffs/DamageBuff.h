#pragma once

namespace TowerDefense
{
	class DamageBuff : public Buff
	{
	public:
		DamageBuff(int duration, int source, Tower::DamageType type, float modifier);
		void Apply(Tower::Tower& t) override;
		void Remove(Tower::Tower& t) override;

	private:
		Tower::DamageType m_Type;
		float m_Modifier;
	};
}