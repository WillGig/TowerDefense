#pragma once

namespace TowerDefense
{
	class Time
	{
	public:
		Time(const Time&) = delete;
		static Time& Get();
		void Update();
		int GetTime();
	private:
		Time();
		int m_Time;
	};
}