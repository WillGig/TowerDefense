#include "pch.h"
#include "SaveLoad.h"
#include "TowerDefense.h"
#include "Player.h"
#include "scenes/Combat.h"
#include "cards/HeroCard.h"
#include "scenes/Base.h"
#include "scenes/random_events/RandomEvent.h"

void TowerDefense::Save::SaveSettings()
{
	std::ofstream settingsFile;
	settingsFile.open("res/saves/settings.dat");

	settingsFile << TowerDefense::FPSShowing();
	settingsFile << "\n" << TowerDefense::GetFrameCap();

	settingsFile.close();
}

void TowerDefense::Save::SaveGame(int slot)
{
	std::ofstream saveFile;
	saveFile.open("res/saves/save" + std::to_string(slot) + ".dat");

	//Player Data
	Player& player = Player::Get();
	saveFile << player.GetHealth() << "\n";
	saveFile << player.GetMaxHealth() << "\n";
	saveFile << player.GetEnergy() << "\n";
	saveFile << player.GetResource(Resource::GOLD) << "\n";
	saveFile << player.GetResource(Resource::WOOD) << "\n";
	saveFile << player.GetResource(Resource::STONE) << "\n";
	saveFile << player.GetResource(Resource::WHEAT) << "\n";
	saveFile << player.GetResourceGatherRate(Resource::GOLD) << "\n";
	saveFile << player.GetResourceGatherRate(Resource::WOOD) << "\n";
	saveFile << player.GetResourceGatherRate(Resource::STONE) << "\n";
	saveFile << player.GetResourceGatherRate(Resource::WHEAT) << "\n";
	saveFile << player.GetPopulation() << "\n";
	saveFile << player.GetMaxPopulation() << "\n";
	saveFile << player.GetNumHouses() << "\n";
	saveFile << player.GetWorkers(Resource::WOOD) << "\n";
	saveFile << player.GetWorkers(Resource::STONE) << "\n";
	saveFile << player.GetWorkers(Resource::WHEAT) << "\n";
	saveFile << player.GetDamageDealt() << "\n";
	saveFile << player.GetAmountHealed() << "\n";
	saveFile << player.GetEnemiesDefeated() << "\n";
	saveFile << player.GetScore() << "\n";

	//Day
	saveFile << TowerDefense::GetDay() << "\n";

	//Combats
	saveFile << Combat::GetFightNumber() << "\n";
	std::vector<int> fightOrder = Combat::GetFightOrder();
	for (unsigned int i = 0; i < fightOrder.size(); i++)
		saveFile << fightOrder[i] << "\n";

	//Cards
	auto cards = Player::Get().GetDeck();
	saveFile << cards->GetSize() << "\n";
	for (int i = 0; i < cards->GetSize(); i++)
	{
		auto card = cards->GetCard(i);
		if (auto hero = std::dynamic_pointer_cast<HeroCard>(card))
		{
			saveFile << "hero\n";
			saveFile << hero->GetName() << "\n";
			saveFile << hero->GetCost() << "\n";
			saveFile << hero->GetImageName() << "\n";
			saveFile << hero->GetTower()->GetName() << "\n"; //May be hero name instead of which tower it is
			auto quirks = hero->GetQuirks();
			saveFile << quirks->at(0)->GetName() << "\n";
			saveFile << quirks->at(1)->GetName() << "\n";
			saveFile << quirks->at(2)->GetName() << "\n";
			saveFile << quirks->at(3)->GetName() << "\n";
		}
		else
		{
			saveFile << "normal\n";
			saveFile << card->GetName() << "\n";
			saveFile << card->IsUpgraded() << "\n";
		}
	}

	//Artifacts
	auto artifacts = Player::Get().GetArtifacts();
	saveFile << artifacts->GetSize() << "\n";
	for (int i = 0; i < artifacts->GetSize(); i++)
	{
		saveFile << artifacts->GetArtifact(i)->GetName() << "\n";
		saveFile << artifacts->GetArtifact(i)->GetSaveData();
	}

	//Buildings
	auto baseScenes = Base::GetBaseScenes();
	saveFile << baseScenes->size() << "\n";
	for (unsigned int i = 0; i < baseScenes->size(); i++)
	{
		saveFile << baseScenes->at(i)->GetName() << "\n";
		saveFile << baseScenes->at(i)->GetActivityReady() << "\n";
	}

	//Events
	auto remainingEvents = RandomEvent::GetRemainingEvents();
	saveFile << remainingEvents->size() << "\n";
	for (unsigned int i = 0; i < remainingEvents->size(); i++)
	{
		saveFile << remainingEvents->at(i)->GetName() << "\n";
	}

	//Seed
	saveFile << Random::Get().GetState() << "\n";
	saveFile << Random::Get().GetDistState();

	saveFile.close();
}

void TowerDefense::Load::LoadSettings()
{
	std::ifstream settingsFile("res/saves/settings.dat");
	if (settingsFile.is_open())
	{
		std::string line;

		try
		{
			//Show FPS
			std::getline(settingsFile, line);
			if (line[0] == '0')
				ShowFPS(false);
			else
				ShowFPS(true);

			//FPS Cap
			std::getline(settingsFile, line);
			SetFrameCap(std::stoi(line));
		}
		catch(const std::exception& ex)
		{

			std::cout << "Error reading settings file. Default settings will be used." << std::endl;
			std::cout << ex.what() << std::endl;
		}
		
	}
	else 
		std::cout << "Failed to find settings file. Default settings will be used." << std::endl;
}

void TowerDefense::Load::LoadGame(int slot)
{

}