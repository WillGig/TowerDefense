#include "pch.h"
#include "SaveLoad.h"
#include "TowerDefense.h"
#include "Player.h"
#include "scenes/Combat.h"
#include "cards/HeroCard.h"
#include "scenes/Base.h"
#include "scenes/random_events/RandomEvent.h"
#include "towers/Ranger.h"
#include "towers/Wizard.h"
#include "towers/Bard.h"
#include "towers/Cleric.h"
#include "towers/Paladin.h"

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

	//File Info
	saveFile << TowerDefense::GetDay() << "\n";
	time_t now = time(0);
	saveFile << std::ctime(&now);

	//Player Data
	Player& player = Player::Get();
	saveFile << player.GetMaxHealth() << "\n";
	saveFile << player.GetHealth() << "\n";
	saveFile << player.GetEnergy() << "\n";
	saveFile << player.GetResource(Resource::GOLD) << "\n";
	saveFile << player.GetResource(Resource::WOOD) << "\n";
	saveFile << player.GetResource(Resource::STONE) << "\n";
	saveFile << player.GetResource(Resource::WHEAT) << "\n";
	saveFile << player.GetResourceGatherRate(Resource::WOOD) << "\n";
	saveFile << player.GetResourceGatherRate(Resource::STONE) << "\n";
	saveFile << player.GetResourceGatherRate(Resource::WHEAT) << "\n";
	saveFile << player.GetResourceGatherRate(Resource::EXPLORE) << "\n";
	saveFile << player.GetMaxPopulation() << "\n";
	saveFile << player.GetPopulation() << "\n";
	saveFile << player.GetNumHouses() << "\n";
	saveFile << player.GetWorkers(Resource::WOOD) << "\n";
	saveFile << player.GetWorkers(Resource::STONE) << "\n";
	saveFile << player.GetWorkers(Resource::WHEAT) << "\n";
	saveFile << player.GetDamageDealt() << "\n";
	saveFile << player.GetAmountHealed() << "\n";
	saveFile << player.GetEnemiesDefeated() << "\n";
	saveFile << player.GetScore() << "\n";
	saveFile << player.GetSideBoardSlots()->size() << "\n";

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
			saveFile << hero->GetImageName() << "\n";
			saveFile << hero->GetTowerClass() << "\n";
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
	std::cout << "Loading Save File..." << std::endl;

	Base::SaveSlot = slot;

	std::ifstream saveFile("res/saves/save" + std::to_string(slot) + ".dat");
	if (saveFile.is_open())
	{
		std::string line;
		try
		{
			//Day
			std::cout << "...Day Data" << std::endl;
			std::getline(saveFile, line);
			TowerDefense::SetDay(std::stoi(line));
			Player::Get().UpdateDayText();

			//Date of save
			std::getline(saveFile, line);

			//Player Data
			std::cout << "...Player Data" << std::endl;
			Player& player = Player::Get();
			std::getline(saveFile, line);
			player.SetMaxHealth(std::stoi(line));
			std::getline(saveFile, line);
			player.SetHealth(std::stoi(line));
			std::getline(saveFile, line);
			player.SetEnergy(std::stoi(line));

			std::getline(saveFile, line);
			player.SetResource(std::stoi(line), Resource::GOLD);
			std::getline(saveFile, line);
			player.SetResource(std::stoi(line), Resource::WOOD);
			std::getline(saveFile, line);
			player.SetResource(std::stoi(line), Resource::STONE);
			std::getline(saveFile, line);
			player.SetResource(std::stoi(line), Resource::WHEAT);
			std::getline(saveFile, line);
			player.SetResourceGatherRate(std::stoi(line), Resource::WOOD);
			std::getline(saveFile, line);
			player.SetResourceGatherRate(std::stoi(line), Resource::STONE);
			std::getline(saveFile, line);
			player.SetResourceGatherRate(std::stoi(line), Resource::WHEAT);
			std::getline(saveFile, line);
			player.SetResourceGatherRate(std::stoi(line), Resource::EXPLORE);

			std::getline(saveFile, line);
			player.SetMaxPopulation(std::stoi(line));
			std::getline(saveFile, line);
			player.SetPopulation(std::stoi(line));
			std::getline(saveFile, line);
			player.SetNumHouses(std::stoi(line));
			std::getline(saveFile, line);
			player.SetNumWorkers(std::stoi(line), Resource::WOOD);
			std::getline(saveFile, line);
			player.SetNumWorkers(std::stoi(line), Resource::STONE);
			std::getline(saveFile, line);
			player.SetNumWorkers(std::stoi(line), Resource::WHEAT);

			std::getline(saveFile, line);
			player.SetDamageDealt(std::stoi(line));
			std::getline(saveFile, line);
			player.SetAmountHealed(std::stoi(line));
			std::getline(saveFile, line);
			player.SetEnemiesDefeated(std::stoi(line));
			std::getline(saveFile, line);
			player.SetScore(std::stoi(line));

			std::getline(saveFile, line);
			int numSlots = std::stoi(line);
			player.ClearSideBoardSlots();
			for (int i = 0; i < numSlots; i++)
				player.AddSideBoardSlot();

			//Combats
			std::cout << "...Combat Data" << std::endl;
			std::getline(saveFile, line);
			Combat::SetFightNumber(std::stoi(line));
			std::vector<int> fightOrder(20);
			for (int i = 0; i < 20; i++)
			{
				std::getline(saveFile, line);
				fightOrder.push_back(std::stoi(line));
			}
			Combat::GenerateFightsFromOrder(fightOrder);

			//Cards
			std::cout << "...Card Data" << std::endl;
			player.ClearDeck();
			player.ClearArtifacts();

			std::getline(saveFile, line);
			int deckSize = std::stoi(line);
			for (int i = 0; i < deckSize; i++)
			{
				std::getline(saveFile, line);
				if (line == "normal")
				{
					std::getline(saveFile, line);
					auto card = Card::GetCardFromName(line);
					std::getline(saveFile, line);
					if (line == "1")
						card->Upgrade();
					player.AddToDeck(card);
				}
				else if (line == "hero")
				{
					std::getline(saveFile, line);
					std::string name = line;
					std::getline(saveFile, line);
					std::string texture = line;
					std::getline(saveFile, line);
					std::string towerName = line;

					auto quirks = std::make_shared<std::vector<std::shared_ptr<Quirk::Quirk>>>();

					for (int i = 0; i < 4; i++)
					{
						std::getline(saveFile, line);
						quirks->push_back(Quirk::Quirk::GetQuirkFromName(line));
					}

					std::string text = "Class:  " + towerName + "\nRace:  " + quirks->at(0)->GetName() + "\n";

					for (unsigned int i = 1; i < quirks->size(); i++)
						text += quirks->at(i)->GetName() + "\n";

					int cost;
					std::shared_ptr<Tower::Tower> heroTower;
					if (towerName == "Ranger") {
						heroTower = std::make_shared<Tower::Ranger>();
						cost = 100;
					}
					else if (towerName == "Wizard") {
						heroTower = std::make_shared<Tower::Wizard>();
						cost = 100;
					}
					else if (towerName == "Bard") {
						heroTower = std::make_shared<Tower::Bard>();
						cost = 50;
					}
					else if (towerName == "Cleric") {
						heroTower = std::make_shared<Tower::Cleric>();
						cost = 50;
					}
					else if (towerName == "Paladin") {
						heroTower = std::make_shared<Tower::Paladin>();
						cost = 100;
					}
					else
					{
						std::cout << "Error: Failed to identify tower type of hero card: " << towerName << std::endl;
						continue;
					}

					player.AddToDeck(std::make_shared<HeroCard>(name, text, cost, texture, heroTower, quirks));
				}
			}

			//Artifacts
			std::cout << "...Artifact Data" << std::endl;
			std::getline(saveFile, line);
			int numArtifacts = std::stoi(line);

			for (int i = 0; i < numArtifacts; i++)
			{
				std::getline(saveFile, line);
				const std::string name = line;
				
				if (name == "Token Of The Mute")
					player.AddArtifactWithoutTrigger(std::make_shared<TokenOfTheMute>());
				else if (name == "Token Of The Armored")
					player.AddArtifactWithoutTrigger(std::make_shared<TokenOfTheArmored>());
				else if (name == "Token Of The Broken")
					player.AddArtifactWithoutTrigger(std::make_shared<TokenOfTheBroken>());
				else if (name == "Token Of The Vigilant")
				{
					std::getline(saveFile, line);
					player.AddArtifactWithoutTrigger(std::make_shared<TokenOfTheVigilant>(std::stoi(line)));
				}
				else if (name == "Lucky Axe")
					player.AddArtifactWithoutTrigger(std::make_shared<LuckyAxe>());
				else if (name == "Lucky Pickaxe")
					player.AddArtifactWithoutTrigger(std::make_shared<LuckyPickaxe>());
				else if (name == "Lucky Sythe")
					player.AddArtifactWithoutTrigger(std::make_shared<LuckySythe>());
				else if (name == "Boulder")
					player.AddArtifactWithoutTrigger(std::make_shared<Boulder>());
				else if (name == "Magic Beans")
					player.AddArtifactWithoutTrigger(std::make_shared<MagicBeans>());
				else if (name == "Fruit Cake")
					player.AddArtifactWithoutTrigger(std::make_shared<FruitCake>());
				else if (name == "Doll House")
					player.AddArtifactWithoutTrigger(std::make_shared<DollHouse>());
				else if (name == "Toy Dolls")
				{
					std::getline(saveFile, line);
					player.AddArtifactWithoutTrigger(std::make_shared<ToyDolls>(std::stoi(line)));
				}
				else if (name == "Hand Of Midas")
					player.AddArtifactWithoutTrigger(std::make_shared<HandOfMidas>());
				else if (name == "House Expansion Kit")
					player.AddArtifactWithoutTrigger(std::make_shared<HouseExpansionKit>());
				else if (name == "Thermos")
					player.AddArtifactWithoutTrigger(std::make_shared<Thermos>());
				else if (name == "Cooler")
				{
					std::getline(saveFile, line);
					player.AddArtifactWithoutTrigger(std::make_shared<Cooler>(std::stoi(line)));
				}
				else if (name == "Miniature WormHole")
					player.AddArtifactWithoutTrigger(std::make_shared<MiniatureWormHole>());
				else if (name == "Special Toxins")
					player.AddArtifactWithoutTrigger(std::make_shared<SpecialToxins>());
				else if (name == "Extra Slot")
					player.AddArtifactWithoutTrigger(std::make_shared<ExtraSlot>());
				else if (name == "Shrubbery")
					player.AddArtifactWithoutTrigger(std::make_shared<Shrubbery>());
				else if (name == "Explorers Hat")
					player.AddArtifactWithoutTrigger(std::make_shared<ExplorersHat>());
				else if (name == "Map To Eldorado")
				{
					std::getline(saveFile, line);
					player.AddArtifactWithoutTrigger(std::make_shared<MapToEldorado>(std::stoi(line)));
				}
				else
					std::cout << "Error: Artifact " << name << " does not exist" << std::endl;
			}

			//Buildings
			std::cout << "...Building Data" << std::endl;
			Base::ClearBaseScenes();

			std::getline(saveFile, line);
			int numBuildings = std::stoi(line);

			for (int i = 0; i < numBuildings; i++)
			{
				std::getline(saveFile, line);
				const std::string name = line;
				std::getline(saveFile, line);
				int activityReady = std::stoi(line);

				if (name == "Gather Resources")
					Base::AddBaseScene(std::make_shared<GatherResources>());
				else if (name == "Rest")
					Base::AddBaseScene(std::make_shared<Rest>());
				else if (name == "Library")
					Base::AddBaseScene(std::make_shared<Library>());
				else if (name == "Smithing")
					Base::AddBaseScene(std::make_shared<Smithing>());
				else if (name == "Tavern")
					Base::AddBaseScene(std::make_shared<Tavern>());
				else if (name == "Chapel")
					Base::AddBaseScene(std::make_shared<Chapel>());
				else if (name == "Build")
					Base::AddBaseScene(std::make_shared<Build>());
				else if (name == "Trader")
					Base::AddBaseScene(std::make_shared<Trader>());
				else if (name == "ManageWorkers")
					Base::AddBaseScene(std::make_shared<ManageWorkers>());
				else if (name == "Joust")
					Base::AddBaseScene(std::make_shared<Joust>());
				else if (name == "ArcheryRange")
					Base::AddBaseScene(std::make_shared<ArcheryRange>());
				else if (name == "WizardTower")
					Base::AddBaseScene(std::make_shared<WizardTower>());
				else if (name == "Temple")
					Base::AddBaseScene(std::make_shared<Temple>());
				else if (name == "AlchemyLab")
					Base::AddBaseScene(std::make_shared<AlchemyLab>());
				else if (name == "MusicHall")
					Base::AddBaseScene(std::make_shared<MusicHall>());
				else
				{
					std::cout << "Error: Base Scene " << name << " does not exist" << std::endl;
					continue;
				}
				Base::GetBaseScenes()->at(Base::GetBaseScenes()->size() - 1)->SetActivityReady(activityReady);
			}

			//Events
			std::cout << "...Event Data" << std::endl;
			std::shared_ptr<std::vector<std::shared_ptr<RandomEvent>>> eventsRemaining = std::make_shared<std::vector<std::shared_ptr<RandomEvent>>>();

			std::getline(saveFile, line);
			int numEvents = std::stoi(line);

			for (int i = 0; i < numEvents; i++)
			{
				std::getline(saveFile, line);
				const std::string name = line;

				if (name == "FountainOfYouth")
					eventsRemaining->push_back(std::make_shared<FountainOfYouth>());
				else if (name == "Devil")
					eventsRemaining->push_back(std::make_shared<LiterallySatan>());
				else if (name == "CaveBat")
					eventsRemaining->push_back(std::make_shared<CaveBat>());
				else if (name == "Trolley")
					eventsRemaining->push_back(std::make_shared<TrolleyProblem>());
				else if (name == "KnightsWhoSayNah")
					eventsRemaining->push_back(std::make_shared<KnightsWhoSayNah>());
				else if (name == "FrogPrince")
					eventsRemaining->push_back(std::make_shared<FrogPrince>());
				else if (name == "Treasure")
					eventsRemaining->push_back(std::make_shared<Treasure>());
				else if (name == "WanderingSage")
					eventsRemaining->push_back(std::make_shared<WanderingSage>());
				else if (name == "WanderingBard")
					eventsRemaining->push_back(std::make_shared<WanderingBard>());
				else if (name == "WanderingCleric")
					eventsRemaining->push_back(std::make_shared<WanderingCleric>());
				else if (name == "BlackKnight")
					eventsRemaining->push_back(std::make_shared<TheBlackKnight>());
			}
			RandomEvent::SetRemainingEvents(eventsRemaining);

			//Seed
			std::cout << "...Seed Data" << std::endl;
			std::mt19937 randGen;
			saveFile >> randGen;

			std::uniform_real_distribution<float> dist;
			saveFile >> dist;

			Random::Get().SetState(randGen);
			Random::Get().SetDistribution(dist);

			SetScene(SceneType::BASE);
		}
		catch (const std::exception& ex)
		{

			std::cout << "Error reading save file. Returning to main menu" << std::endl;
			std::cout << ex.what() << std::endl;
			SetScene(SceneType::MAINMENU);
		}

	}
	else
	{
		std::cout << "Failed to find save file. Returning to main menu." << std::endl;
		SetScene(SceneType::MAINMENU);
	}
}