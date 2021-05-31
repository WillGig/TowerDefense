#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::ToyDolls::ToyDolls()
	:Artifact("Toy Dolls"), m_NumberAdded(0)
{}

void TowerDefense::ToyDolls::OnAquire()
{
	Player& player = Player::Get();
	int numToAdd = player.GetNumHouses();
	if (player.GetMaxPopulation() - player.GetPopulation() >= numToAdd)
	{
		player.SetPopulation(player.GetPopulation() + numToAdd);
		m_NumberAdded = numToAdd;
	}
	else
	{
		m_NumberAdded = player.GetMaxPopulation() - player.GetPopulation();
		player.SetPopulation(player.GetMaxPopulation());
	}
}

void TowerDefense::ToyDolls::OnAddHouse()
{
	Player& player = Player::Get();
	int numToAdd = player.GetNumHouses() - m_NumberAdded;
	if (player.GetMaxPopulation() - player.GetPopulation() >= numToAdd)
	{
		player.SetPopulation(player.GetPopulation() + numToAdd);
		m_NumberAdded += numToAdd;
	}
	else
	{
		m_NumberAdded += player.GetMaxPopulation() - player.GetPopulation();
		player.SetPopulation(player.GetMaxPopulation());
	}
}