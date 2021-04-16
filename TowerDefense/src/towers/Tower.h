#pragma once
#include "buffs/Buff.h"
#include "cards/CardChoice.h"

namespace TowerDefense 
{
	class Buff;

	namespace Tower
	{
		enum class TowerType { DAMAGE, SUPPORT };
		enum class Targeting { FIRST, LAST, CLOSE, STRONG, WEAK };
		enum class DamageType { PHYSICAL, MAGIC };

		class Tower : public Entity
		{
		public:
			Tower(float x, float y, int width, int height, float fireTime, int range, TowerType type, const std::string& regularImage, const std::string& highlightedImage);

			void Update() override;

			void Destroy();

			virtual std::shared_ptr<Tower> Clone() = 0;

			void SetX(float x) override;
			void SetY(float y) override;

			inline int GetRange() const { return m_Range; }
			inline void SetRange(int range) { m_Range = range; }

			inline float GetAttackTime() const { return m_FireTime; }
			inline void SetAttackTime(float speed) { m_FireTime = speed; }

			inline float GetDamageModifier(DamageType type) const { return type == DamageType::PHYSICAL ? m_PhysicalDamageModifier : m_MagicDamageModifier; }
			inline void SetDamageModifier(float modifier, DamageType type) { type == DamageType::PHYSICAL ? m_PhysicalDamageModifier = modifier : m_MagicDamageModifier = modifier; }

			inline float GetCritChance() const { return m_CritChance; }
			inline void SetCritChance(float chance) { m_CritChance = chance; }

			inline float GetCritMultiplier() const { return m_CritMultiplier; }
			inline void SetCritMultiplier(float multiplier) { m_CritMultiplier = multiplier; }

			inline void SetHighlighted() { m_Highlighted = true; }

			inline bool GetClicked() { return m_Clicked; };

			inline std::shared_ptr<Circle> GetRangeCircle() const { return m_RangeCircle; }

			inline TowerType GetType() const { return m_TowerType; }

			std::shared_ptr<CardChoice> GetUpgrades();

			void ApplyBuff(std::shared_ptr<Buff> buff);

			void RemoveBuff(int buffID);

			void ClearBuffs();

			bool IsBuffedBy(Tower& t);

		protected:
			virtual void Fire(std::shared_ptr<TowerDefense::Entity> target) = 0;
			virtual void Clicked();
			float FindDirection(float x, float y);
			bool ContainsCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>> exclude, std::shared_ptr<Card> card);
			virtual std::shared_ptr<Card> GetRandomUpgrade(std::shared_ptr<std::vector<std::shared_ptr<Card>>> exclude);


			float m_PhysicalDamage, m_PhysicalDamageModifier, m_MagicDamage, m_MagicDamageModifier, m_Spread, m_CritChance, m_CritMultiplier;

		private:
			std::shared_ptr<TowerDefense::Entity> FindTarget();
			void UpdateImage();
			void Attack();
			void UpdateBuffs();

			//Attack period in Game Updates (60 per second)
			float m_FireTime;
			int m_LastFire, m_Range;
			bool m_Highlighted, m_Clicked;
			TowerType m_TowerType;
			Targeting m_TargetType;

			std::shared_ptr<Image> m_RegularImage, m_HighlightedImage;
			std::shared_ptr<Circle> m_RangeCircle;

			std::unique_ptr<std::vector<std::shared_ptr<Buff>>> m_Buffs, m_AddBuffs;
			std::unique_ptr<std::vector<unsigned int>> m_RemoveBuffs;
		};

	}
}