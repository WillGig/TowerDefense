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
		inline virtual void OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type) {};
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

	class PoisonWeapons : public Aura
	{
	public:
		PoisonWeapons(float poisonDamage, int poisonDuration, const std::string dmg);
		void OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type) override;

	private:
		float m_PoisonDamage;
		int m_PoisonDuration;
	};

	class StunAttacks : public Aura
	{
	public:
		StunAttacks(int stunDuration, const std::string duration);
		void OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type) override;

	private:
		int m_StunDuration;
	};

	class ConstantDamage : public Aura
	{
	public:
		ConstantDamage(float damage, int time, const std::string damagePerTime);
		void Update() override;

	private:
		float m_Damage;
		int m_Time, m_NextDamage;
	};

	class DeathExplosions : public Aura
	{
	public:
		DeathExplosions(int damage);
		void OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e) override;

	private:
		int m_Damage, m_Radius;
	};

	class Storm : public Aura
	{
	public:
		Storm(int damage);
		void OnCardPlay(std::shared_ptr<Card> c) override;

	private:
		std::vector<std::shared_ptr<TowerDefense::Enemy::Enemy>> GetTargets();
		std::shared_ptr<TowerDefense::Enemy::Enemy> GetEnemyInRange(std::shared_ptr<Enemy::Enemy> currentEnemy, std::vector<std::shared_ptr<Enemy::Enemy>> exclude, float range);
		bool Contains(std::vector<std::shared_ptr<Enemy::Enemy>> list, unsigned int ID);

		int m_Damage;
	};

	class EnhancePoison : public Aura
	{
	public:
		//Damage string should be double extra damage, since poison ticks twice per second
		EnhancePoison(float extraDamage, const std::string damage);
		void OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type) override;

	private:
		float m_ExtraDamage;
	};
}