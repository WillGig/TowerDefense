#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"

TowerDefense::ManageWorkers::ManageWorkers()
	:BaseScene("manageWorkersButton", "Assign Tasks", 0),
	m_BackToCamp(std::make_unique<Button>(690.0f, 60.0f, 180, 50, "returnToCampButton")),
	m_WoodPlus(std::make_unique<Button>(200.0f, 400.0f, 32, 32, "plus")), 
	m_WoodMinus(std::make_unique<Button>(250.0f, 400.0f, 32, 32, "minus")), 
	m_StonePlus(std::make_unique<Button>(200.0f, 350.0f, 32, 32, "plus")),
	m_StoneMinus(std::make_unique<Button>(250.0f, 350.0f, 32, 32, "minus")),
	m_WheatPlus(std::make_unique<Button>(200.0f, 300.0f, 32, 32, "plus")),
	m_WheatMinus(std::make_unique<Button>(250.0f, 300.0f, 32, 32, "minus")),
	m_BuildHouse(std::make_unique<Button>(250.0f, 200.0f, 180, 50, "buildHouseButton")),
	m_HireWorker(std::make_unique<Button>(550.0f, 200.0f, 180, 50, "hireWorkerButton")),
	m_TotalText(std::make_unique<Text>("Total", 350.0f, 500.0f, 12.0f, 0.0f)),
	m_AvailableText(std::make_unique<Text>("Available", 333.0f, 450.0f, 12.0f, 0.0f)),
	m_LumberjacksText(std::make_unique<Text>("Lumberjacks", 334.0f, 400.0f, 12.0f, 0.0f)),
	m_MinersText(std::make_unique<Text>("Miners", 310.0f, 350.0f, 12.0f, 0.0f)),
	m_FarmersText(std::make_unique<Text>("Farmers", 318.0f, 300.0f, 12.0f, 0.0f)),
	m_BuildCost(std::make_unique<Text>("100          100", 230.0f, 150.0f, 12.0f, 0.0f)),
	m_WorkerCost(std::make_unique<Text>("50", 540.0f, 150.0f, 12.0f, 0.0f)),
	m_WorkerImage(std::make_unique<Image>("workerIcon", 385.0f, 500.0f, 20, 20, 0.0f)),
	m_WorkerAvailableImage(std::make_unique<Image>("workerIcon", 385.0f, 450.0f, 20, 20, 0.0f)),
	m_WoodImage(std::make_unique<Image>("woodIcon", 220.0f, 150.0f, 20, 20, 0.0f)),
	m_StoneImage(std::make_unique<Image>("stoneIcon", 310.0f, 150.0f, 20, 20, 0.0f)),
	m_WheatImage(std::make_unique<Image>("wheatIcon", 580.0f, 150.0f, 20, 20, 0.0f))
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
	m_StonePlus->Render();
	m_StoneMinus->Render();
	m_WheatPlus->Render();
	m_WheatMinus->Render();
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

	m_WorkerImage->Render();
	m_WorkerAvailableImage->Render();
	m_WoodImage->Render();
	m_StoneImage->Render();
	m_WheatImage->Render();

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
		m_StonePlus->Update();
		m_StoneMinus->Update();
		m_WheatPlus->Update();
		m_WheatMinus->Update();
		m_BuildHouse->Update();
		m_HireWorker->Update();
		m_BackToCamp->Update();

		if (m_WoodPlus->IsClicked() && player.GetAvailablePopulation() > 0)
		{
			player.AddWorker(Resource::WOOD);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 420.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumLumberJacks = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WOOD)), 570.0f, 400.0f, 12.0f, 0.0f);
			m_NumLumberJacks->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (m_WoodMinus->IsClicked() && player.GetWorkers(Resource::WOOD) > 0)
		{
			player.RemoveWorker(Resource::WOOD);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 420.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumLumberJacks = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WOOD)), 570.0f, 400.0f, 12.0f, 0.0f);
			m_NumLumberJacks->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_StonePlus->IsClicked() && player.GetAvailablePopulation() > 0)
		{
			player.AddWorker(Resource::STONE);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 420.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumMiners = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::STONE)), 570.0f, 350.0f, 12.0f, 0.0f);
			m_NumMiners->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (m_StoneMinus->IsClicked() && player.GetWorkers(Resource::STONE) > 0)
		{
			player.RemoveWorker(Resource::STONE);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 420.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumMiners = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::STONE)), 570.0f, 350.0f, 12.0f, 0.0f);
			m_NumMiners->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_WheatPlus->IsClicked() && player.GetAvailablePopulation() > 0)
		{
			player.AddWorker(Resource::WHEAT);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 420.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumFarmers = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WHEAT)), 570.0f, 300.0f, 12.0f, 0.0f);
			m_NumFarmers->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (m_WheatMinus->IsClicked() && player.GetWorkers(Resource::WHEAT) > 0)
		{
			player.RemoveWorker(Resource::WHEAT);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 420.0f, 450.0f, 12.0f, 0.0f);
			m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_NumFarmers = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WHEAT)), 570.0f, 300.0f, 12.0f, 0.0f);
			m_NumFarmers->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_BuildHouse->IsClicked() && player.GetResource(Resource::WOOD) > 99 && player.GetResource(Resource::STONE) > 99)
		{
			player.ChangeResource(-100, Resource::WOOD);
			player.ChangeResource(-100, Resource::STONE);
			player.AddHouse();
			m_TotalPopText = std::make_unique<Text>(std::to_string(player.GetPopulation()) + "/" + std::to_string(player.GetMaxPopulation()), 420.0f, 500.0f, 12.0f, 0.0f);
			m_TotalPopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_HireWorker->IsClicked() && player.GetResource(Resource::WHEAT) > 49 && player.GetMaxPopulation() - player.GetPopulation() > 0)
		{
			player.ChangeResource(-50, Resource::WHEAT);
			player.SetPopulation(player.GetPopulation() + 1);
			m_TotalPopText = std::make_unique<Text>(std::to_string(player.GetPopulation()) + "/" + std::to_string(player.GetMaxPopulation()), 420.0f, 500.0f, 12.0f, 0.0f);
			m_TotalPopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 420.0f, 450.0f, 12.0f, 0.0f);
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
	m_TotalPopText = std::make_unique<Text>(std::to_string(player.GetPopulation()) + "/" + std::to_string(player.GetMaxPopulation()), 420.0f, 500.0f, 12.0f, 0.0f);
	m_TotalPopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_AvailablePopText = std::make_unique<Text>(std::to_string(player.GetAvailablePopulation()), 420.0f, 450.0f, 12.0f, 0.0f);
	m_AvailablePopText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_NumLumberJacks = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WOOD)), 570.0f, 400.0f, 12.0f, 0.0f);
	m_NumLumberJacks->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_NumMiners = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::STONE)), 570.0f, 350.0f, 12.0f, 0.0f);
	m_NumMiners->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_NumFarmers = std::make_unique<Text>(std::to_string(player.GetWorkers(Resource::WHEAT)), 570.0f, 300.0f, 12.0f, 0.0f);
	m_NumFarmers->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}