#pragma once
#include "cards/HeroCard.h"

namespace TowerDefense
{

	class HeroCard;

	namespace Quirk
	{
		enum class Gender { MALE, FEMALE };
		enum class QuirkType { RACE, POSITIVE, NEGATIVE };

		class Quirk
		{
		public:
			Quirk(const std::string& name);
			virtual void Apply(TowerDefense::HeroCard& h);
			virtual void OnPlay();
			inline std::string GetName() const { return m_Name; }
			virtual std::shared_ptr<Quirk> Clone() = 0;

			static std::shared_ptr<std::vector<std::shared_ptr<Quirk>>> GenerateQuirks();

		private:
			std::string m_Name;

			static std::shared_ptr<Quirk> GetRandomQuirk(QuirkType type, std::shared_ptr<std::vector<std::shared_ptr<Quirk>>> exclude);
			static bool Contains(std::shared_ptr<std::vector<std::shared_ptr<Quirk>>> quirks, std::shared_ptr<Quirk> q);
		};

		//RACES
		class Human : public Quirk
		{
		public:
			Human();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class Dwarf : public Quirk
		{
		public:
			Dwarf();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class HighElf : public Quirk
		{
		public:
			HighElf();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class WoodElf : public Quirk
		{
		public:
			WoodElf();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class Gnome : public Quirk
		{
		public:
			Gnome();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class Orc : public Quirk
		{
		public:
			Orc();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class Giant : public Quirk
		{
		public:
			Giant();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		//POSITIVE
		class BattleReady : public Quirk
		{
		public:
			BattleReady();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class Explorer : public Quirk
		{
		public:
			Explorer();
			void OnPlay() override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class JustLucky : public Quirk
		{
		public:
			JustLucky();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class Veteran : public Quirk
		{
		public:
			Veteran();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class Farsighted : public Quirk
		{
		public:
			Farsighted();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class Spellweaver : public Quirk
		{
		public:
			Spellweaver();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class Fighter : public Quirk
		{
			Fighter();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class Sage : public Quirk
		{
		public:
			Sage();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		class Berserker : public Quirk
		{
			Berserker();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

		//NEGATIVE
		class Nearsighted : public Quirk
		{
		public:
			Nearsighted();
			void Apply(TowerDefense::HeroCard& h) override;
			std::shared_ptr<Quirk> Clone() override;
		};

	}
}