#pragma once
#include "cards/CardChoice.h"

namespace TowerDefense
{
	class CombatReward : public Button
	{
	public:
		CombatReward(const std::string msg);
		virtual void Render() override;
		void Update() override;
		virtual void SetPosition(float x, float y);
		inline void SetX(float x) override { SetPosition(x, m_Y); };
		inline void SetY(float y) override { SetPosition(m_X, y); };
		inline bool RewardTaken() { return m_RewardTaken; }
		inline bool RequiresFocus() { return m_RequiresFocus; }
		inline bool ShowingInfo() { return m_ShowingInfo; }

	private:
		virtual void OnClicked() = 0;

	protected:
		bool m_RewardTaken, m_RequiresFocus, m_ShowingInfo;
		std::unique_ptr<Text> m_Text;
	};

	class GoldReward : public CombatReward
	{
	public:
		GoldReward(int amount);
		void Render() override;
		void SetPosition(float x, float y) override;

	private:
		void OnClicked() override;

		int m_GoldAmount;
		std::unique_ptr<Image> m_CoinImage;
	};

	class CardReward : public CombatReward
	{
	public:
		CardReward(int numChoices);
		void Render() override;
		void Update() override;
		void SetPosition(float x, float y) override;

	private:
		void OnClicked() override;

		std::unique_ptr<CardChoice> m_CardChoice;
		std::unique_ptr<Button> m_Confirm, m_Cancel;
		std::unique_ptr<Rectangle> m_Fade;
	};
}