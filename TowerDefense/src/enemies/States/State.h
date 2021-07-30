#pragma once
#include "enemies/Enemy.h"

namespace TowerDefense
{
	namespace Enemy
	{
		class Enemy;

		enum class StateType { SLOW, STUN, ARMORREDUCTION, MAGICRESISTREDUCTION };

		class State
		{
		public:
			State(int time, StateType type);

			void Update();

			virtual void OnApply(Enemy& e) = 0;

			virtual void OnRemove(Enemy& e) = 0;

			virtual void OnCombine(Enemy& e, std::shared_ptr<State> other) = 0;

			inline bool Active() const { return m_Active; }

			inline StateType GetType() const { return m_Type; }

		protected:
			int m_TimeRemaining;

		private:
			bool m_Active;
			StateType m_Type;
		};

		class Slow : public State
		{
		public:
			Slow(int time, float slowPercent);
			void OnApply(Enemy& e) override;
			void OnRemove(Enemy& e) override;
			void OnCombine(Enemy& e, std::shared_ptr<State> other) override;

		private:
			float m_SlowPercent;
		};

		class Stun : public State
		{
		public:
			Stun(int time);
			void OnApply(Enemy& e) override;
			void OnRemove(Enemy& e) override;
			void OnCombine(Enemy& e, std::shared_ptr<State> other) override;
		};

		class ArmorReduction : public State
		{
		public:
			ArmorReduction(int time, float reductionPercent);
			void OnApply(Enemy& e) override;
			void OnRemove(Enemy& e) override;
			void OnCombine(Enemy& e, std::shared_ptr<State> other) override;
		};

		class MagicResistReduction : public State
		{
		public:
			MagicResistReduction(int time, float reductionPercent);
			void OnApply(Enemy& e) override;
			void OnRemove(Enemy& e) override;
			void OnCombine(Enemy& e, std::shared_ptr<State> other) override;
		};

	}
}