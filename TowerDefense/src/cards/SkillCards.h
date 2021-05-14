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

	class PoisonBall : public Card
	{
	public:
		PoisonBall();
		void Render() override;
		void Update() override;
		void Upgrade() override;
		bool Play() override;
		std::shared_ptr<Card> Clone() override;

	private:
		float m_PoisonAmount, m_Radius;
		int m_PoisonTime;

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

	class Sift : public Card
	{
	public:
		Sift();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Reflect : public Card
	{
	public:
		Reflect();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Skim : public Card
	{
	public:
		Skim();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Refresh : public Card
	{
	public:
		Refresh();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Center : public Card
	{
	public:
		Center();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Gather : public Card
	{
	public:
		Gather();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Concentrate : public Card
	{
	public:
		Concentrate();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Recharge : public Card
	{
	public:
		Recharge();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Attain : public Card
	{
	public:
		Attain();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Ren : public Card
	{
	public:
		Ren();
		void Upgrade() override;
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class Surge : public Card
	{
	public:
		Surge();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};

	class MassStun : public Card
	{
	public:
		MassStun();
		bool Play() override;
		std::shared_ptr<Card> Clone() override;
	};
}