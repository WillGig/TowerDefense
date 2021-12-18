#pragma once

namespace TowerDefense
{
	class Random
	{
	public:
		Random(const Random&) = delete;

		//Generates a new seed
		void NewSeed();

		inline unsigned int GetSeed() { return m_Seed; }
		//Sets generator to specified seed so that runs can be reproduced
		void SetSeed(unsigned int seed);

		inline const std::mt19937& GetState() const { return m_Generator; }

		inline void SetState(std::mt19937 gen) { m_Generator = gen; }

		inline const std::uniform_real_distribution<float>& GetDistState() const { return m_Distribution; }

		inline void SetDistribution(std::uniform_real_distribution<float> dist) { m_Distribution = dist; }

		static Random& Get();

		//Returns random float from 0 to 1
		static inline float GetFloat() { return Get().FloatImp(); }

	private:
		Random();
		//Generates random float from 0 to 1 using the seeded generator
		float FloatImp();

		unsigned int m_Seed;
		std::mt19937 m_Generator;
		std::uniform_real_distribution<float> m_Distribution;
	};
}