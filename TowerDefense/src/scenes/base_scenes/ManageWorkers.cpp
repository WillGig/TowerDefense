#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"

TowerDefense::ManageWorkers::ManageWorkers()
	:BaseScene("manageWorkersButton", "Assign Tasks", 0),
	m_BackToCamp(std::make_unique<Button>(690.0f, 60.0f, 180, 50, "returnToCampButton")),
	m_WoodPlus(std::make_unique<Button>(250.0f, 400.0f, 32, 32, "plus")), 
	m_WoodMinus(std::make_unique<Button>(300.0f, 400.0f, 32, 32, "minus")), 
	m_WoodAddAll(std::make_unique<Button>(200.0f, 400.0f, 47, 35, "addAll")),
	m_WoodMinusAll(std::make_unique<Button>(350.0f, 400.0f, 47, 35, "minusAll")),
	m_StonePlus(std::make_unique<Button>(250.0f, 350.0f, 32, 32, "plus")),
	m_StoneMinus(std::make_unique<Button>(300.0f, 350.0f, 32, 32, "minus")),
	m_StoneAddAll(std::make_unique<Button>(200.0f, 350.0f, 47, 35, "addAll")),
	m_StoneMinusAll(std::make_unique<Button>(350.0f, 350.0f, 47, 35, "minusAll")),
	m_WheatPlus(std::make_unique<Button>(250.0f, 300.0f, 32, 32, "plus")),
	m_WheatMinus(std::make_unique<Button>(300.0f, 300.0f, 32, 32, "minus")),
	m_WheatAddAll(std::make_unique<Button>(200.0f, 300.0f, 47, 35, "addAll")),
	m_WheatMinusAll(std::make_unique<Button>(350.0f, 300.0f, 47, 35, "minusAll")),
	m_BuildHouse(std::make_unique<Button>(325.0f, 200.0f, 128, 50, "buildHouseButton")),
	m_HireWorker(std::make_unique<Button>(475.0f, 200.0f, 128, 50, "hireWorkerButton")),
	m_TotalText(std::make_unique<Text>("Total", 397.0f, 500.0f, 12.0f, 0.0f)),
	m_AvailableText(std::make_unique<Text>("Available", 373.0f, 450.0f, 12.0f, 0.0f)),
	m_LumberjacksText(std::make_unique<Text>("Lumberjacks", 434.0f, 400.0f, 12.0f, 0.0f)),
	m_MinersText(std::make_unique<Text>("Miners", 410.0f, 350.0f, 12.0f, 0.0f)),
	m_FarmersText(std::make_unique<Text>("Farmers", 418.0f, 300.0f, 12.0f, 0.0f)),
	m_BuildCost(std::make_unique<Text>("100      100", 310.0f, 150.0f, 12.0f, 0.0f)),
	m_WorkerCost(std::make_unique<Text>("50", 460.0f, 150.0f, 12.0f, 0.0f)),
	m_WorkerImage(std::make_unique<Image>("workerIcon", 432.0f, 500.0f, 20, 20, 0.0f)),
	m_HouseImage(std::make_unique<Image>("houseIcon", 347.0f, 500.0f, 32, 32, 0.0f)),
	m_WorkerAvailableImage(std::make_unique<Image>("workerIcon", 425.0f, 450.0f, 20, 20, 0.0f)),
	m_WoodImage(std::make_unique<Image>("woodIcon", 310.0f, 150.0f, 20, 20, 0.0f)),
	m_StoneImage(std::make_unique<Image>("stoneIcon", 375.0f, 150.0f, 20, 20, 0.0f)),
	m_WheatImage(std::make_unique<Image>("wheatIcon", 490.0f, 150.0f, 20, 20, 0.0f))
{
	m_TotalText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_AvailableText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_LumberjacksText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_MinersText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_FarmersText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_BuildCost->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_WorkerCost->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::ManageWorkers::Render()
{
	Player& player = Player::Get();
	player.RenderStats();

	m_WoodPlus->Render();
	m_WoodMinus->Render();
	m_WoodAddAll->Render();
	m_WoodMinusAll->Render();
	m_StonePlus->Render();
	m_StoneMinus->Render();
	m_StoneAddAll->Render();
	m_StoneMinusAll->Render();
	m_WheatPlus->Render();
	m_WheatMinus->Render();
	m_WheatAddAll->Render();
	m_WheatMinusAll->Render();
	m_BuildHouse->Render();
	m_HireWorker->Render();
	m_BackToCamp->Render();

	m_TotalText->Render();
	m_AvailableText->Render();
	m_LumberjacksText->Render();
	m_MinersText->Render();
	m_FarmersText->Render();
	m_BuildCost->Render();
	m_WorkerCost->Render();

	m_HouseImage->Render();
	m_WorkerImage->Render();
	m_WorkerAvailableImage->Render();
	m_WoodImage->Render();
	m_StoneImage->Render();
	m_WheatImage->Render();

	m_HouseText->Render();
	m_TotalPopText->Render();
	m_AvailablePopText->Render();
	m_NumLumberJacks->Render();
	m_NumMiners->Render();
	m_NumFarmers->Render();

	player.RenderDeckAndArtifacts();
}

void TowerDefense::ManageWorkers::Update()
{
	Player& player = Player::Get();

	player.UpdateDeckAndArtifacts();

	if (!player.DeckShowing() && !player.ArtifactsShowing())
	{
		m_WoodPlus->Update();
		m_WoodMinus->Update();
		m_WoodAddAll->Update();
		m_WoodMinusAll->Update();
		m_StonePlus->Update();
		m_StoneMinus->Update();
		m_StoneAddAll->Update();
		m_StoneMinusAll->Update();
		m_WheatPlus->Update();
		m_WheatMinus->Update();
		m_WheatAddAll->Update();
		m_WheatMinusAll->Update();
		m_BuildHouse->Update();
		m_HireWorker->Update();
		m_BackToCamp->Update();

		if (m_WoodPlus->IsClicked() && player.GetAvailablePopulation() > 0)
		{
			player.AddWorker(Resource::WOOD);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumLumberJacks = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WOOD)), 620.0f, 400.0f, 12.0f, 0.0f);
			m_NumLumberJacks->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (m_WoodMinus->IsClicked() && player.GetWorkers(Resource::WOOD) > 0)
		{
			player.RemoveWorker(Resource::WOOD);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumLumberJacks = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WOOD)), 620.0f, 400.0f, 12.0f, 0.0f);
			m_NumLumberJacks->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (m_WoodAddAll->IsClicked() && player.GetAvailablePopulation() > 0)
		{
			while (player.GetAvailablePopulation() > 0)
				player.AddWorker(Resource::WOOD);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumLumberJacks = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WOOD)), 620.0f, 400.0f, 12.0f, 0.0f);
			m_NumLumberJacks->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (m_WoodMinusAll->IsClicked() && player.GetWorkers(Resource::WOOD) > 0)
		{
			while(player.GetWorkers(Resource::WOOD) > 0)
				player.RemoveWorker(Resource::WOOD);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumLumberJacks = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WOOD)), 620.0f, 400.0f, 12.0f, 0.0f);
			m_NumLumberJacks->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_StonePlus->IsClicked() && player.GetAvailablePopulation() > 0)
		{
			player.AddWorker(Resource::STONE);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumMiners = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::STONE)), 620.0f, 350.0f, 12.0f, 0.0f);
			m_NumMiners->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (m_StoneMinus->IsClicked() && player.GetWorkers(Resource::STONE) > 0)
		{
			player.RemoveWorker(Resource::STONE);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumMiners = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::STONE)), 620.0f, 350.0f, 12.0f, 0.0f);
			m_NumMiners->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (m_StoneAddAll->IsClicked() && player.GetAvailablePopulation() > 0)
		{
			while(player.GetAvailablePopulation() > 0)
				player.AddWorker(Resource::STONE);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumMiners = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::STONE)), 620.0f, 350.0f, 12.0f, 0.0f);
			m_NumMiners->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (m_StoneMinusAll->IsClicked() && player.GetWorkers(Resource::STONE) > 0)
		{
			while(player.GetWorkers(Resource::STONE) > 0)
				player.RemoveWorker(Resource::STONE);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumMiners = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::STONE)), 620.0f, 350.0f, 12.0f, 0.0f);
			m_NumMiners->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_WheatPlus->IsClicked() && player.GetAvailablePopulation() > 0)
		{
			player.AddWorker(Resource::WHEAT);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumFarmers = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WHEAT)), 620.0f, 300.0f, 12.0f, 0.0f);
			m_NumFarmers->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (m_WheatMinus->IsClicked() && player.GetWorkers(Resource::WHEAT) > 0)
		{
			player.RemoveWorker(Resource::WHEAT);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumFarmers = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WHEAT)), 620.0f, 300.0f, 12.0f, 0.0f);
			m_NumFarmers->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (m_WheatAddAll->IsClicked() && player.GetAvailablePopulation() > 0)
		{
			while (player.GetAvailablePopulation() > 0)
				player.AddWorker(Resource::WHEAT);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumFarmers = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WHEAT)), 620.0f, 300.0f, 12.0f, 0.0f);
			m_NumFarmers->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (m_WheatMinusAll->IsClicked() && player.GetWorkers(Resource::WHEAT) > 0)
		{
			while(player.GetWorkers(Resource::WHEAT) > 0)
				player.RemoveWorker(Resource::WHEAT);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumFarmers = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WHEAT)), 620.0f, 300.0f, 12.0f, 0.0f);
			m_NumFarmers->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_BuildHouse->IsClicked() && player.GetResource(Resource::WOOD) > 99 && player.GetResource(Resource::STONE) > 99)
		{
			player.ChangeResource(-100, Resource::WOOD);
			player.ChangeResource(-100, Resource::STONE);
			player.AddHouse();
			m_HouseText = std::make_unique<Text>(std::to_string(player.GetNumHouses()), 317.0f, 500.0f, 12.0f, 0.0f);
			m_HouseText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_TotalPopText = std::make_unique<Text>(std::to_string(player.GetPopulation()) + "/" + std::to_string(player.GetMaxPopulation()), 467.0f, 500.0f, 12.0f, 0.0f);
			m_TotalPopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_HireWorker->IsClicked() && player.GetResource(Resource::WHEAT) > 49 && player.GetMaxPopulation() - player.GetPopulation() > 0)
		{
			player.ChangeResource(-50, Resource::WHEAT);
			player.SetPopulation(player.GetPopulation() + 1);
			m_TotalPopText = std::make_unique<Text>(std::to_string(player.GetPopulation()) + "/" + std::to_string(player.GetMaxPopulation()), 467.0f, 500.0f, 12.0f, 0.0f);
			m_TotalPopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_BackToCamp->IsClicked())
			m_Exit = true;
	}
}

void TowerDefense::ManageWorkers::OnSwitch()
{
	BaseScene::OnSwitch();
	Player& player = Player::Get();
	m_HouseText = std::make_unique<Text>(std::to_string(player.GetNumHouses()), 317.0f, 500.0f, 12.0f, 0.0f);
	m_HouseText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_TotalPopText = std::make_unique<Text>(std::to_string(player.GetPopulation()) + "/" + std::to_string(player.GetMaxPopulation()), 467.0f, 500.0f, 12.0f, 0.0f);
	m_TotalPopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 460.0f, 450.0f, 12.0f, 0.0f);
	m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_NumLumberJacks = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WOOD)), 620.0f, 400.0f, 12.0f, 0.0f);
	m_NumLumberJacks->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_NumMiners = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::STONE)), 620.0f, 350.0f, 12.0f, 0.0f);
	m_NumMiners->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_NumFarmers = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WHEAT)), 620.0f, 300.0f, 12.0f, 0.0f);
	m_NumFarmers->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}