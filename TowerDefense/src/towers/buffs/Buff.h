#pragma once
#include "towers/Tower.h"

namespace TowerDefense
{
	namespace Tower
	{
		class Tower;
	}

	class Buff
	{
	public:
		Buff(int duration, int source);
		void Update(Tower::Tower& t);
		virtual void Apply(Tower::Tower& t) = 0;
		virtual void Remove(Tower::Tower& t);
		inline int GetID() const { return m_ID; }
		inline int GetDuration() const { return m_Duration; }
		inline int GetSource() const { return m_Source; }
		inline void SetDuration(int duration) { m_Duration = duration; }

	private:
		//IDs start at 0 and increment each time a buff is created
		static unsigned int s_ID;
		//Unique ID given to each buff to track specific buffs
		unsigned int m_ID;
		int m_Duration, m_Source;
	};
}