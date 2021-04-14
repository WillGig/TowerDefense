#pragma once
#include "Wave.h"

namespace TowerDefense
{
	class Fight
	{
	public:
		Fight(std::shared_ptr<std::vector<std::shared_ptr<Wave>>> waves);
		inline bool HasMoreWaves() const { return m_CurrentWave < (int)m_Waves->size() - 1; }
		inline std::shared_ptr<Wave> GetWave() const {return m_CurrentWave == -1 ? nullptr : m_Waves->at(m_CurrentWave); }
		inline void NextWave() { m_CurrentWave++; }

	private:
		int m_CurrentWave;
		std::shared_ptr<std::vector<std::shared_ptr<Wave>>> m_Waves;
	};
}