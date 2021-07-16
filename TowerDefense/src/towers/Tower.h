#pragma once
#include "buffs/Buff.h"
#include "cards/CardChoice.h"

namespace TowerDefense 
{
	class Buff;

	namespace Tower
	{
		class Upgrade;

		enum class TowerType { DAMAGE, SUPPORT };
		enum class TargetType { FIRST, LAST, CLOSE, STRONG, WEAK };
		enum class DamageType { PHYSICAL, MAGIC, POISON, TRUE};

		class Tower : public Entity
		{
		public:
			Tower(float x, float y, int width, int height, float fireTime, int range, TowerType type, const std::string& name);

			void Update() override;

			void Destroy();

			virtual std::shared_ptr<Tower> Clone() = 0;

			void SetX(float x) override;
			void SetY(float y) override;

			inline std::string GetName() const { return m_Name; }
			inline void SetName(const std::string& name) { m_Name = name; }

			void SetImage(const std::string& image);

			inline void SetLevel(int level) { m_Level = level; }
			inline int GetLevel() const { return m_Level; }
			int GetUpgradeCost() const;

			inline int GetRange() const { return m_Range; }
			void SetRange(int range);
			inline float GetAttackTime() const { return m_FireTime; }
			inline void SetAttackTime(float speed) { m_FireTime = speed; }

			inline float GetDamage(DamageType type) const { return type == DamageType::PHYSICAL ? m_PhysicalDamage : m_MagicDamage; }
			inline void SetDamage(float modifier, DamageType type) { type == DamageType::PHYSICAL ? m_PhysicalDamage = modifier : m_MagicDamage = modifier; }

			inline DamageType GetDamageType() const { return m_DamageType; }

			inline TargetType GetTargetType() const { return m_TargetType; }
			inline void SetTargetType(TargetType t) { m_TargetType = t; }

			inline float GetCritChance() const { return m_CritChance; }
			inline void SetCritChance(float chance) { m_CritChance = chance; }

			inline float GetCritMultiplier() const { return m_CritMultiplier; }
			inline void SetCritMultiplier(float multiplier) { m_CritMultiplier = multiplier; }

			inline float GetArmorPenChance() const { return m_ArmorPenChance; }
			inline void SetArmorPenChance(float chance) { m_ArmorPenChance = chance; }

			inline float GetArmorPenReduction() const { return m_ArmorPenReduction; }
			inline void SetArmorPenReduction(float reduction) { m_ArmorPenReduction = reduction; }

			inline float GetDamageDealt() const { return m_TotalDamageDealt; }
			inline void AddDamageDealt(float damage) { m_TotalDamageDealt += damage; }

			inline bool CanSeeInvisibility() const { return m_SeeInvisibility; }
			inline void SetSeeInvisilitity(bool see) { m_SeeInvisibility = see; }

			inline void SetHighlighted() { m_Highlighted = true; }

			inline bool GetClicked() { return m_Clicked; };

			inline std::shared_ptr<Circle> GetRangeCircle() const { return m_RangeCircle; }

			inline TowerType GetType() const { return m_TowerType; }

			virtual bool CanUpgrade() = 0;

			std::shared_ptr<CardChoice> GetUpgrades();

			std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> GetTowerUpgrades();

			void ApplyBuff(std::shared_ptr<Buff> buff);

			void RemoveBuff(int buffID);

			void ClearBuffs();

			bool IsBuffedBy(Tower& t);

		protected:
			virtual std::shared_ptr<TowerDefense::Entity> FindTarget();
			virtual void Attack();
			virtual void Fire(std::shared_ptr<TowerDefense::Entity> target) = 0;
			virtual void Clicked();
			float FindDirection(float x, float y);
			bool ContainsCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>> exclude, std::shared_ptr<Card> card);
			bool ContainsUpgrade(std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> exclude, std::shared_ptr<Upgrade> upgrade);
			virtual std::shared_ptr<Card> GetRandomUpgrade(std::shared_ptr<std::vector<std::shared_ptr<Card>>> exclude);
			virtual std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> GetPossibleUpgrades();

			DamageType m_DamageType;

			bool m_SeeInvisibility;

			int m_FireReady;

			float m_PhysicalDamage, m_MagicDamage, m_Spread, m_CritChance, m_CritMultiplier, m_ArmorPenChance, m_ArmorPenReduction;

		private:
			void UpdateImage();
			void UpdateBuffs();

			//Attack period in Game Updates (60 per second)
			float m_FireTime, m_TotalDamageDealt;
			int m_Range, m_Level;
			bool m_Highlighted, m_Clicked;
			TowerType m_TowerType;
			TargetType m_TargetType;
			std::string m_Name;

			std::shared_ptr<Image> m_RegularImage, m_HighlightedImage;
			std::shared_ptr<Circle> m_RangeCircle;

			std::unique_ptr<std::vector<std::shared_ptr<Buff>>> m_Buffs, m_AddBuffs;
			std::unique_ptr<std::vector<unsigned int>> m_RemoveBuffs;

			std::shared_ptr<std::vector<std::shared_ptr<Upgrade>>> m_Upgrades;
		};

	}
}