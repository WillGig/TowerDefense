#pragma once

namespace TowerDefense
{
	class Random
	{
	public:
		Random(const Random&) = delete;

		//Generates a new seed
		void NewSeed();

		//Sets generator to specified seed so that runs can be reproduced
		void SetSeed(unsigned int seed);

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