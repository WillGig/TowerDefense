
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
	}
}