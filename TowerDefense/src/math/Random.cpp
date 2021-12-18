#include "pch.h"
#include "Random.h"

TowerDefense::Random::Random()
	:m_Seed(0)
{}

TowerDefense::Random& TowerDefense::Random::Get()
{
	static Random instance;
	return instance;
}

void TowerDefense::Random::NewSeed()
{
	std::random_device rd;
	m_Seed = rd();
	std::cout << "Seed: " << m_Seed << std::endl;
	m_Generator = std::mt19937(m_Seed);
	m_Distribution = std::uniform_real_distribution<float>(0.0f, 1.0f);
}

void TowerDefense::Random::SetSeed(unsigned int seed)
{
	m_Seed = seed;
	std::cout << "Seed: " << m_Seed << std::endl;
	m_Generator = std::mt19937(m_Seed);
	m_Distribution = std::uniform_real_distribution<float>(0.0f, 1.0f);
}

float TowerDefense::Random::FloatImp()
{
	return m_Distribution(m_Generator);
}