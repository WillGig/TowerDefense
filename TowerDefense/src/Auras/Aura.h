#pragma once
#include "cards/Card.h"
#include "enemies/Enemy.h"

namespace TowerDefense
{
	class Aura : public Entity
	{
	public:
		Aura(const std::string name, const std::string info);
		void Render() override;
		virtual void Update() override;
		void SetX(float x) override;
		void SetY(float y) override;
		inline virtual void OnAquire() {};
		inline virtual void OnCardPlay(std::shared_ptr<Card> c) {};
		inline virtual void OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source) {};
		inline virtual void OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e) {};

	private:
		std::string m_Name;
		bool m_Selected;
		std::unique_ptr<Image> m_InfoImage;
		std::unique_ptr<Text> m_InfoText;
	};

	class LifeSteal : public Aura
	{
	public:
		LifeSteal(int steal);
		void OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e) override;

	private:
		int m_LifeSteal;
	};
}