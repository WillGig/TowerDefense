#include "pch.h"
#include "SaveLoad.h"
#include "TowerDefense.h"
#include "Player.h"

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
	saveFile << Player::Get().GetHealth() << "\n";
	saveFile << Player::Get().GetMaxHealth() << "\n";
	saveFile << Player::Get().GetEnergy() << "\n";
	saveFile << Player::Get().GetResource(Resource::GOLD) << "\n";
	saveFile << Player::Get().GetResource(Resource::WOOD) << "\n";
	saveFile << Player::Get().GetResource(Resource::STONE) << "\n";
	saveFile << Player::Get().GetResource(Resource::WHEAT) << "\n";
	saveFile << Player::Get().GetResourceGatherRate(Resource::GOLD) << "\n";
	saveFile << Player::Get().GetResourceGatherRate(Resource::WOOD) << "\n";
	saveFile << Player::Get().GetResourceGatherRate(Resource::STONE) << "\n";
	saveFile << Player::Get().GetResourceGatherRate(Resource::WHEAT) << "\n";

	//Day
	saveFile << TowerDefense::GetDay() << "\n";


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
		}
		
	}
	else 
		std::cout << "Failed to find settings file. Default settings will be used." << std::endl;
}

void TowerDefense::Load::LoadGame(int slot)
{

}