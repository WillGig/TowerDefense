#pragma once
#include "Scene.h"
#include "CombatReward.h"

namespace TowerDefense
{
	class PostCombatScreen : public Scene
	{
	public:
		PostCombatScreen();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
	private:
		void AddReward(std::shared_ptr<CombatReward> reward);
		void RemoveReward(int reward);

		int m_FocusedReward;
		std::unique_ptr<Button> m_BackToCamp;
		std::unique_ptr<std::vector<std::shared_ptr<CombatReward>>> m_Rewards;
		std::unique_ptr<Text> m_VictoryText, m_DefeatedStats, m_EscapedStats, m_DamageDealt;
	};
}
