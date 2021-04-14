#include "pch.h"
#include "Combat.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "core/Board.h"
#include "enemies/Enemies.h"
#include "towers/Archer.h"

int TowerDefense::Combat::s_RoundSpeed = 1;

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Entity>>> TowerDefense::Combat::s_Entities = std::make_shared<std::vector<std::shared_ptr<TowerDefense::Entity>>>();
std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Entity>>> TowerDefense::Combat::s_Adders = std::make_shared<std::vector<std::shared_ptr<TowerDefense::Entity>>>();
std::shared_ptr<std::vector<int>> TowerDefense::Combat::s_Removers = std::make_shared<std::vector<int>>();
std::unique_ptr<std::vector<std::shared_ptr<TowerDefense::Fight>>> TowerDefense::Combat::s_Fights = std::make_unique<std::vector<std::shared_ptr<TowerDefense::Fight>>>();

TowerDefense::Combat::Combat()
	:m_PlayerHealth(Player::Get().GetHealth()), m_PlayerEnergy(Player::Get().GetEnergy()), m_CurrentFight(-1),
	m_Paused(false), m_TurnPhase(Phase::START),
	m_ViewDeck(std::make_unique<Button>(50, 43, 570.0f, 578.0f, "res/textures/viewDeckButton.png", "res/textures/viewDeckButtonSelected.png")),
	m_StartButton(std::make_unique<Button>(96, 32, 76.0f, 201.0f, "res/textures/startButton.png", "res/textures/startButtonSelected.png")),
	m_SpeedButton(std::make_unique<Button>(96, 32, 76.0f, 159.0f, "res/textures/speed1.png", "res/textures/speed1Selected.png")),
	m_Health(std::make_unique<Text>(std::string("Health: ") + std::to_string(Player::Get().GetHealth()), 610.0f, 575.0f, 10.0f, 0.0f)), 
	m_Energy(std::make_unique<Text>(std::string("Energy: ") + std::to_string(Player::Get().GetEnergy()), 700.0f, 575.0f, 10.0f, 0.0f)),
	m_Day(std::make_unique<Text>(std::string("Day: ") + std::to_string(GetDay()), 400.0f, 575.0f, 10.0f, 0.0f))
{
	//Set Draw and discard piles to be shown in random orders
	Player::Get().GetDrawPile()->SetOrdered(false);
	Player::Get().GetDiscardPile()->SetOrdered(false);
	Player::Get().GetDeck()->SetOrdered(true);
	m_Health->SetColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Energy->SetColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Day->SetColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TowerDefense::Combat::Render()
{
	//Board
	Board::Get().Render();

	//Towers, Enemies, Projectiles
	for (unsigned int i = 0; i < s_Entities->size(); i++)
		s_Entities->at(i)->Render();

	//Range Indicator
	if (m_SelectedTower)
		m_SelectedTower->GetRangeCircle()->Render();

	//Buttons
	m_ViewDeck->Render();
	m_StartButton->Render();
	m_SpeedButton->Render();

	//Drawpile, Discardpile, Hand
	RenderCards();

	//Stats at top of screen
	m_Health->Render();
	m_Energy->Render();
	m_Day->Render();
}

void TowerDefense::Combat::Update()
{
	Board::Get().Update();

	UpdateCards();

	UpdateWave();

	bool deckShow = Player::Get().GetDeck()->IsShowing();
	bool drawShow = Player::Get().GetDrawPile()->IsShowing();
	bool discardShow = Player::Get().GetDiscardPile()->IsShowing();
	bool cardSelected = Player::Get().GetHand()->GetSelectedCard() != -1;
	if (!cardSelected && !deckShow && !drawShow && !discardShow) 
	{
		UpdateButtons();
		FindSelectedTower();
	}

	UpdateEntities();

	UpdateHealthandEnergy();
}

void TowerDefense::Combat::OnSwitch()
{
	//Change Background Color
	Renderer::Get().Clear(237.0f / 255.0f, 225.0f / 255.0f, 190.0f / 255.0f, 1.0f);

	//Reset Combat
	Player::Get().SetEnergy(100);
	Player::Get().ResetCardPiles();
	m_TurnPhase = Phase::START;

	m_StartButton->SetImages("res/textures/startButton.png", "res/textures/startButtonSelected.png");
	m_SelectedTower.reset();

	ClearProjectiles();
	ClearTowers();

	//Update Day Text
	m_Day = std::make_unique<Text>(std::string("Day: ") + std::to_string(GetDay()), 400.0f, 575.0f, 10.0f, 0.0f);

	m_CurrentFight++;
}

//Called at end of program to clean up memory
//Necessary to unbind static and singleton GLFW textures before calling glfwTerminate
void TowerDefense::Combat::CleanUp()
{
	s_Entities.reset();
	s_Adders.reset();
	s_Removers.reset();
	s_Fights.reset();
}

//Draw Hand, Deck, Draw Pile, and Discard Pile
void TowerDefense::Combat::RenderCards()
{
	Player& player = Player::Get();

	player.GetDrawPile()->Render();
	player.GetDiscardPile()->Render();
	player.GetHand()->Render();

	if (player.GetDrawPile()->IsShowing())
	{
		player.GetDrawPile()->RenderCards();
		player.GetDrawPile()->Render();
	}
	if (player.GetDiscardPile()->IsShowing())
	{
		player.GetDiscardPile()->RenderCards();
		player.GetDiscardPile()->Render();
	}

	if (player.GetDeck()->IsShowing())
	{
		player.GetDeck()->RenderCards();
		m_ViewDeck->Render();
	}
}

//Update All Towers, Projectiles, and Enemies
//Add all new enemies, towers, and projectiles and remove all deleted ones 
void TowerDefense::Combat::UpdateEntities()
{
	//Update Entities
	if (!m_Paused)
	{
		for (unsigned int i = 0; i < s_Entities->size(); i++)
			s_Entities->at(i)->Update();
	}

	//Add all entities from adders and clear
	for (unsigned int i = 0; i < s_Adders->size(); i++)
		s_Entities->push_back(s_Adders->at(i));
	s_Adders->clear();

	//Remove all entities from removers and clear
	for (unsigned int i = 0; i < s_Removers->size(); i++)
	{
		for (unsigned int j = 0; j < s_Entities->size(); j++)
		{
			if (s_Removers->at(i) == s_Entities->at(j)->GetID())
			{
				s_Entities->erase(s_Entities->begin() + j);
				break;
			}
		}
	}
	s_Removers->clear();
}

//Updates Hand, Draw pile, Discard pile, and View Deck button
void TowerDefense::Combat::UpdateCards()
{
	Player& player = Player::Get();
	bool deckShow = player.GetDeck()->IsShowing();
	bool drawShow = player.GetDrawPile()->IsShowing();
	bool discardShow = player.GetDiscardPile()->IsShowing();
	bool cardSelected = player.GetHand()->GetSelectedCard() != -1;

	if (!m_Paused && !deckShow && !drawShow && !discardShow)
		player.GetHand()->Update();
	if (!cardSelected && !drawShow && !discardShow)
	{
		player.GetDeck()->Update();
		m_ViewDeck->Update();
		if (m_ViewDeck->IsClicked())
			player.GetDeck()->Show(!player.GetDeck()->IsShowing());
	}
	if (!cardSelected && !deckShow && !discardShow)
		player.GetDrawPile()->Update();
	if (!cardSelected && !deckShow && !drawShow)
		player.GetDiscardPile()->Update();
}

void TowerDefense::Combat::UpdateWave()
{
	//Check if wave is over and End Round
	auto wave = s_Fights->at(m_CurrentFight)->GetWave();
	if (m_TurnPhase == Phase::COMBAT && (!wave || !wave->HasMoreEnemies()) && EnemiesDefeated())
	{
		m_TurnPhase = Phase::END;
		EndRound();
	}

	//Add new Enemies from wave
	if (m_TurnPhase == Phase::COMBAT && wave->HasMoreEnemies() && !m_Paused) {
		std::shared_ptr<Enemy::Enemy> e = s_Fights->at(m_CurrentFight)->GetWave()->GetNextEnemy();
		if (e)
			AddEntity(e);
	}
}

//Check if start and speed buttons are clicked 
void TowerDefense::Combat::UpdateButtons()
{
	//Start Button
	if (s_Fights->at(m_CurrentFight)->HasMoreWaves() || m_TurnPhase != Phase::START)
	{
		m_StartButton->Update();
		if (m_StartButton->IsClicked())
		{
			if (m_TurnPhase == Phase::START)
			{
				s_Fights->at(m_CurrentFight)->NextWave();
				m_TurnPhase = Phase::COMBAT;
				m_StartButton->SetImages("res/textures/pause.png", "res/textures/pauseSelected.png");
				ClearProjectiles();
			}
			else if (m_TurnPhase == Phase::COMBAT)
			{
				m_Paused = !m_Paused;
			}
			else if (m_TurnPhase == Phase::END)
			{
				m_TurnPhase = Phase::START;
				Player::Get().DrawHand();
				m_StartButton->SetImages("res/textures/startButton.png", "res/textures/startButtonSelected.png");
			}
		}
	}

	//Speed Button
	m_SpeedButton->Update();
	if (m_SpeedButton->IsClicked())
	{
		if (s_RoundSpeed == 1) {
			s_RoundSpeed = 2;
			m_SpeedButton->SetImages("res/textures/speed2.png", "res/textures/speed2Selected.png");
		}
		else if (s_RoundSpeed == 2) {
			s_RoundSpeed = 3;
			m_SpeedButton->SetImages("res/textures/speed3.png", "res/textures/speed3Selected.png");
		}
		else {
			s_RoundSpeed = 1;
			m_SpeedButton->SetImages("res/textures/speed1.png", "res/textures/speed1Selected.png");
		}
	}
}

//Find if a tower has been clicked, or deselected
void TowerDefense::Combat::FindSelectedTower()
{
	if (Input::GetMouseClicked())
		m_SelectedTower.reset();
	for (unsigned int i = 0; i < s_Entities->size(); i++)
	{
		if (s_Entities->at(i)->GetEntityType() == Type::TOWER)
		{
			auto tower = std::dynamic_pointer_cast<Tower::Tower>(s_Entities->at(i));
			if (tower->GetClicked())
				m_SelectedTower = tower;
		}
	}
}

//Update Player Health and Energy Text
void TowerDefense::Combat::UpdateHealthandEnergy()
{
	Player& player = Player::Get();
	if (m_PlayerHealth != player.GetHealth())
	{
		m_Health = std::make_unique<Text>(std::string("Health: ") + std::to_string(player.GetHealth()), 610.0f, 575.0f, 10.0f, 0.0f);
		m_PlayerHealth = player.GetHealth();
	}

	if (m_PlayerEnergy != player.GetEnergy())
	{
		m_Energy = std::make_unique<Text>(std::string("Energy: ") + std::to_string(player.GetEnergy()), 700.0f, 575.0f, 10.0f, 0.0f);
		m_PlayerEnergy = player.GetEnergy();
	}
}

//Triggers all end round properties of towers and switches scene if combat is over
void TowerDefense::Combat::EndRound()
{
	for (unsigned int i = 0; i < s_Entities->size(); i++)
		s_Entities->at(i)->EndRound();

	m_StartButton->SetImages("res/textures/endButton.png", "res/textures/endButtonSelected.png");

	if(!s_Fights->at(m_CurrentFight)->HasMoreWaves())
		SetScene(SceneType::POSTCOMBAT);
}

//Checks if there are any remaining enemies on the board
//Does NOT check if there are remaining enemies in the wave
bool TowerDefense::Combat::EnemiesDefeated()
{
	for (unsigned int i = 0; i < s_Entities->size(); i++)
	{
		if (s_Entities->at(i)->GetEntityType() == Type::ENEMY)
			return false;
	}
	return true;
}

void TowerDefense::Combat::ClearProjectiles()
{
	for (unsigned int i = 0; i < s_Entities->size(); i++)
	{
		std::shared_ptr<Entity> e = s_Entities->at(i);
		if (e->GetEntityType() == Type::PROJECTILE)
			RemoveEntity(e->GetID());
	}
}

void TowerDefense::Combat::ClearTowers()
{
	for (unsigned int i = 0; i < s_Entities->size(); i++)
	{
		std::shared_ptr<Entity> e = s_Entities->at(i);
		//Important to call Tower::Destroy in order to remove the tower from occupied tiles on the board
		if (e->GetEntityType() == Type::TOWER)
			std::dynamic_pointer_cast<Tower::Tower>(e)->Destroy();
	}
}

//Create pools of difficulty for different fights and randomly select fights from the appropriate pools to fill up the s_Fights vector for the run
//Should be called once at the beginning of a run to generate the set of combats
void TowerDefense::Combat::GenerateFights()
{
	//day 1-3 fights
	std::vector<std::shared_ptr<Fight>> pool1;
	auto waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies1[] = { 0, 0, 0, 200, 0, 200, 0, 200 };
	waves->push_back(std::make_shared<Wave>(enemies1, 8));
	pool1.push_back(std::make_shared<Fight>(waves));

	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies2[] = { 0, 0, 0, 200, 0, 200, 0, 200 };
	waves->push_back(std::make_shared<Wave>(enemies2, 8));
	pool1.push_back(std::make_shared<Fight>(waves));

	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies3[] = { 0, 0, 0, 200, 0, 200, 0, 200 };
	waves->push_back(std::make_shared<Wave>(enemies3, 8));
	pool1.push_back(std::make_shared<Fight>(waves));

	//day 4-6 fights
	std::vector<std::shared_ptr<Fight>> pool2;
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies4[] = { 0, 0, 0, 100, 0, 100, 0, 100, 0, 100 };
	const int enemies5[] = { 0, 0, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50 };
	const int enemies6[] = { 0, 0, 0, 50, 0, 50, 1, 150 };
	waves->push_back(std::make_shared<Wave>(enemies4, 10));
	waves->push_back(std::make_shared<Wave>(enemies5, 14));
	waves->push_back(std::make_shared<Wave>(enemies6, 8));
	pool2.push_back(std::make_shared<Fight>(waves));

	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies7[] = { 0, 0, 0, 100, 0, 100, 0, 100, 0, 100 };
	const int enemies8[] = { 0, 0, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50 };
	const int enemies9[] = { 0, 0, 0, 50, 0, 50, 1, 150 };
	waves->push_back(std::make_shared<Wave>(enemies7, 10));
	waves->push_back(std::make_shared<Wave>(enemies8, 14));
	waves->push_back(std::make_shared<Wave>(enemies9, 8));
	pool2.push_back(std::make_shared<Fight>(waves));

	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies10[] = { 0, 0, 0, 100, 0, 100, 0, 100, 0, 100 };
	const int enemies11[] = { 0, 0, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50 };
	const int enemies12[] = { 0, 0, 0, 50, 0, 50, 1, 150 };
	waves->push_back(std::make_shared<Wave>(enemies10, 10));
	waves->push_back(std::make_shared<Wave>(enemies11, 14));
	waves->push_back(std::make_shared<Wave>(enemies12, 8));
	pool2.push_back(std::make_shared<Fight>(waves));

	//day 7-9 fights
	std::vector<std::shared_ptr<Fight>> pool3;
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies13[] = { 2, 0, 2, 100, 2, 100, 2, 100, 2, 100 };
	const int enemies14[] = { 2, 0, 2, 50, 2, 50, 2, 50, 2, 50 };
	const int enemies15[] = { 2, 0, 2, 50, 2, 50, 3, 150, 3, 150 };
	waves->push_back(std::make_shared<Wave>(enemies13, 10));
	waves->push_back(std::make_shared<Wave>(enemies14, 10));
	waves->push_back(std::make_shared<Wave>(enemies15, 10));
	pool3.push_back(std::make_shared<Fight>(waves));

	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies16[] = { 2, 0, 2, 100, 2, 100, 2, 100, 2, 100 };
	const int enemies17[] = { 2, 0, 2, 50, 2, 50, 2, 50, 2, 50 };
	const int enemies18[] = { 2, 0, 2, 50, 2, 50, 3, 150, 3, 150 };
	waves->push_back(std::make_shared<Wave>(enemies16, 10));
	waves->push_back(std::make_shared<Wave>(enemies17, 10));
	waves->push_back(std::make_shared<Wave>(enemies18, 10));
	pool3.push_back(std::make_shared<Fight>(waves));

	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies19[] = { 2, 0, 2, 100, 2, 100, 2, 100, 2, 100 };
	const int enemies20[] = { 2, 0, 2, 50, 2, 50, 2, 50, 2, 50 };
	const int enemies21[] = { 2, 0, 2, 50, 2, 50, 3, 150, 3, 150 };
	waves->push_back(std::make_shared<Wave>(enemies19, 10));
	waves->push_back(std::make_shared<Wave>(enemies20, 10));
	waves->push_back(std::make_shared<Wave>(enemies21, 10));
	pool3.push_back(std::make_shared<Fight>(waves));

	//day 10 fights
	std::vector<std::shared_ptr<Fight>> pool4;
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies22[] = { 0, 0, 0, 50, 0, 50, 0, 50, 0, 50 };
	const int enemies23[] = { 0, 0, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50 };
	const int enemies24[] = { 0, 0, 0, 50, 0, 50, 1, 50 };
	const int enemies25[] = { 0, 0, 0, 50, 0, 50, 0, 50, 0, 50, 1, 50, 0, 50, 0, 50, 1, 50, 0, 50 };
	const int enemies26[] = { 0, 0, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50, 1, 50, 1, 50, 1, 50 };
	const int enemies27[] = { 2, 0, 2, 50, 2, 50, 2, 50, 2, 50 };
	const int enemies28[] = { 0, 0, 0, 25, 0, 25, 0, 25, 0, 25, 2, 50, 2, 50, 2, 50, 2, 50, 2, 50 };
	const int enemies29[] = { 0, 0, 0, 25, 0, 25, 0, 25, 0, 25, 1, 50, 1, 50, 1, 50, 2, 50, 2, 50, 2, 50, 3, 100 };
	const int enemies30[] = { 2, 0, 2, 50, 2, 50, 2, 50, 2, 50, 2, 50, 2, 50, 3, 50, 3, 100, 3, 100 };
	const int enemies31[] = { 4, 0 };
	waves->push_back(std::make_shared<Wave>(enemies22, 10));
	waves->push_back(std::make_shared<Wave>(enemies23, 20));
	waves->push_back(std::make_shared<Wave>(enemies24, 8));
	waves->push_back(std::make_shared<Wave>(enemies25, 20));
	waves->push_back(std::make_shared<Wave>(enemies26, 20));
	waves->push_back(std::make_shared<Wave>(enemies27, 10));
	waves->push_back(std::make_shared<Wave>(enemies28, 20));
	waves->push_back(std::make_shared<Wave>(enemies29, 24));
	waves->push_back(std::make_shared<Wave>(enemies30, 20));
	waves->push_back(std::make_shared<Wave>(enemies31, 2));
	pool4.push_back(std::make_shared<Fight>(waves));


	//determine combats from random pool
	int fight = (int)(Random::GetFloat() * pool1.size());
	s_Fights->push_back(pool1[fight]);
	pool1.erase(pool1.begin() + fight);

	fight = (int)(Random::GetFloat() * pool1.size());
	s_Fights->push_back(pool1[fight]);
	pool1.erase(pool1.begin() + fight);

	fight = (int)(Random::GetFloat() * pool1.size());
	s_Fights->push_back(pool1[fight]);
	pool1.erase(pool1.begin() + fight);

	fight = (int)(Random::GetFloat() * pool2.size());
	s_Fights->push_back(pool2[fight]);
	pool2.erase(pool2.begin() + fight);

	fight = (int)(Random::GetFloat() * pool2.size());
	s_Fights->push_back(pool2[fight]);
	pool2.erase(pool2.begin() + fight);

	fight = (int)(Random::GetFloat() * pool2.size());
	s_Fights->push_back(pool2[fight]);
	pool2.erase(pool2.begin() + fight);

	fight = (int)(Random::GetFloat() * pool3.size());
	s_Fights->push_back(pool3[fight]);
	pool3.erase(pool3.begin() + fight);

	fight = (int)(Random::GetFloat() * pool3.size());
	s_Fights->push_back(pool3[fight]);
	pool3.erase(pool3.begin() + fight);

	fight = (int)(Random::GetFloat() * pool3.size());
	s_Fights->push_back(pool3[fight]);
	pool3.erase(pool3.begin() + fight);

	fight = (int)(Random::GetFloat() * pool4.size());
	s_Fights->push_back(pool4[fight]);
	pool4.erase(pool4.begin() + fight);
}