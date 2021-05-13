#pragma once
#include "Card.h"
#include "enemies/Enemy.h"

namespace TowerDefense
{
	class Focus : public Card {
	public:
		Focus(bool exhausts);
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class PotOfGreed : public Card
	{
	public:
		PotOfGreed();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Double : public Card {
	public:
		Double();
		bool Play() override;
		void Upgrade() override;
		std::shared_ptr<Card> Clone() override;
	};

	class FireBall : public Card
	{
	public:
		FireBall();
		void Render() override;
		void Update() override;
		void Upgrade() override;
		bool Play() override;
		std::shared_ptr<Card> Clone() override;

	private:
		float m_Damage, m_Radius;

		std::unique_ptr<Circle> m_Circle;
	};

	class FrostBall : public Card
	{
	public:
		FrostBall();
		void Render() override;
		void Update() override;
		void Upgrade() override;
		bool Play() override;
		std::shared_ptr<Card> Clone() override;

	private:
		float m_SlowPercent, m_Radius;
		int m_SlowTime;

		std::unique_ptr<Circle> m_Circle;
	};

	class Lightning : public Card
	{
	public:
		Lightning();
		void Render() override;
		void Update() override;
		void Upgrade() override;
		bool Play() override;
		std::shared_ptr<Card> Clone() override;

	private:
		std::shared_ptr<Enemy::Enemy> GetClosestEnemy();
		std::vector<std::shared_ptr<Enemy::Enemy>> GetTargets(std::shared_ptr<Enemy::Enemy> e);
		std::shared_ptr<TowerDefense::Enemy::Enemy> GetEnemyInRange(std::shared_ptr<Enemy::Enemy> e, std::vector<std::shared_ptr<Enemy::Enemy>> exclude, float range);
		bool Contains(std::vector<std::shared_ptr<Enemy::Enemy>> list, unsigned int ID);

		float m_Damage, m_Range;
	};
}