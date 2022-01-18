#pragma once
#include "cards/Card.h"
#include "enemies/Enemy.h"

namespace TowerDefense
{
	namespace Aura
	{
		class Aura : public Entity
		{
		public:
			Aura(const std::string name, const std::string info);
			void Render() override;
			virtual void Update() override;
			virtual void Combine(std::shared_ptr<Aura> other) = 0;
			void SetX(float x) override;
			void SetY(float y) override;
			inline virtual void OnAquire() {};
			inline virtual void OnCardPlay(std::shared_ptr<Card> c) {};
			inline virtual void OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type) {};
			inline virtual void OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e) {};
			inline const std::string& GetName() const { return m_Name; }

		private:
			std::string m_Name;
			bool m_Selected;
			std::unique_ptr<Image> m_InfoImage;
			
		protected:
			std::unique_ptr<Text> m_InfoText;
		};

		class LifeSteal : public Aura
		{
		public:
			LifeSteal(int steal);
			void OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline int GetLifeSteal() const { return m_LifeSteal; }

		private:
			int m_LifeSteal;
		};

		class PoisonWeapons : public Aura
		{
		public:
			PoisonWeapons(float poisonDamage, int poisonDuration);
			void OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline float GetPoisonDamage() const { return m_PoisonDamage; }
			inline int GetPoisonDuration() const { return m_PoisonDuration; }

		private:
			float m_PoisonDamage;
			int m_PoisonDuration;
		};

		class StunAttacks : public Aura
		{
		public:
			StunAttacks(int stunDuration);
			void OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline int GetStunDuration() const { return m_StunDuration; }

		private:
			int m_StunDuration;
		};

		class ConstantDamage : public Aura
		{
		public:
			ConstantDamage(float damage, int time);
			void Update() override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline float GetDamage() const { return m_Damage; }

		private:
			float m_Damage;
			int m_Time, m_NextDamage;
		};

		class DeathExplosions : public Aura
		{
		public:
			DeathExplosions(int damage);
			void OnEnemyDeath(std::shared_ptr<Enemy::Enemy> e) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline int GetDamage() const { return m_Damage; }
			inline int GetRadius() const { return m_Radius; }

		private:
			int m_Damage, m_Radius;
		};

		class Storm : public Aura
		{
		public:
			Storm(int damage);
			void OnCardPlay(std::shared_ptr<Card> c) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline int GetDamage() const { return m_Damage; }

		private:
			std::vector<std::shared_ptr<TowerDefense::Enemy::Enemy>> GetTargets();
			std::shared_ptr<TowerDefense::Enemy::Enemy> GetEnemyInRange(std::shared_ptr<Enemy::Enemy> currentEnemy, std::vector<std::shared_ptr<Enemy::Enemy>> exclude, float range);
			bool Contains(std::vector<std::shared_ptr<Enemy::Enemy>> list, unsigned int ID);

			int m_Damage;
		};

		class EnhancePoison : public Aura
		{
		public:
			EnhancePoison(float extraDamage);
			void OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline float GetExtraDamage() const { return m_ExtraDamage; }

		private:
			float m_ExtraDamage;
		};

		class ArcherDamage : public Aura
		{
		public:
			ArcherDamage(float damage);
			void OnCardPlay(std::shared_ptr<Card> c) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline float GetDamage() const { return m_Damage; }

		private:
			float m_Damage;
		};

		class MultiShot : public Aura
		{
		public:
			MultiShot(int extraShots);
			void OnCardPlay(std::shared_ptr<Card> c) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline int GetExtraShots() const { return m_ExtraShots; }

		private:
			int m_ExtraShots;
		};

		class ArcherCritChance : public Aura
		{
		public:
			ArcherCritChance(float chance);
			void OnCardPlay(std::shared_ptr<Card> c) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline float GetChance() const { return m_Chance; }

		private:
			float m_Chance;
		};

		class ArcherCritDamage : public Aura
		{
		public:
			ArcherCritDamage(float damage);
			void OnCardPlay(std::shared_ptr<Card> c) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline float GetDamage() const { return m_Damage; }

		private:
			float m_Damage;
		};

		class WizardDamage : public Aura
		{
		public:
			WizardDamage(float damage);
			void OnCardPlay(std::shared_ptr<Card> c) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline float GetDamage() const { return m_Damage; }

		private:
			float m_Damage;
		};

		class HolyPower : public Aura
		{
		public:
			HolyPower(float power);
			void OnCardPlay(std::shared_ptr<Card> c) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline float GetPower() const { return m_Power; }

		private:
			float m_Power;
		};

		class MusicPower : public Aura
		{
		public:
			MusicPower(float power);
			void OnCardPlay(std::shared_ptr<Card> c) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline float GetPower() const { return m_Power; }

		private:
			float m_Power;
		};

		class AlchemistDamage : public Aura
		{
		public:
			AlchemistDamage(float damage);
			void OnCardPlay(std::shared_ptr<Card> c) override;
			void Combine(std::shared_ptr<Aura> other) override;
			inline float GetDamage() const { return m_Damage; }

		private:
			float m_Damage;
		};
	}
}