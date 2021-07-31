#pragma once
#include "enemies/Enemy.h"

namespace TowerDefense
{
	namespace Enemy
	{
		class Enemy;

		enum class StateType { SLOW, STUN, ARMORREDUCTION, MAGICRESISTREDUCTION, POISON};

		class State
		{
		public:
			State(int time, StateType type);

			virtual void Update();

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

		private:
			float m_ReductionPercent;
		};

		class MagicResistReduction : public State
		{
		public:
			MagicResistReduction(int time, float reductionPercent);
			void OnApply(Enemy& e) override;
			void OnRemove(Enemy& e) override;
			void OnCombine(Enemy& e, std::shared_ptr<State> other) override;

		private:
			float m_ReductionPercent;
		};

		class Poison : public State
		{
		public:
			Poison(int duration, float damage, unsigned int source, std::shared_ptr<Enemy> target);
			void Update() override;
			void OnApply(Enemy& e) override;
			void OnRemove(Enemy& e) override;
			void OnCombine(Enemy& e, std::shared_ptr<State> other) override;

		private:
			float m_Damage;
			int m_PoisonTick, m_TickRate;
			unsigned int m_Source;
			std::shared_ptr<Enemy> m_Target;
		};

	}
}