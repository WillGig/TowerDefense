#include "pch.h"
#include "Fight.h"

TowerDefense::Fight::Fight(std::shared_ptr<std::vector<std::shared_ptr<Wave>>> waves)
	:m_CurrentWave(-1), m_Waves(waves)
{

}