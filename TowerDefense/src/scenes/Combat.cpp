#include "pch.h"
#include "Combat.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "core/Board.h"
#include "enemies/Enemies.h"
#include "towers/Archer.h"

int TowerDefense::Combat::s_RoundSpeed = 1;
bool TowerDefense::Combat::s_Paused = false;

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Entity>>> TowerDefense::Combat::s_Entities = std::make_shared<std::vector<std::shared_ptr<TowerDefense::Entity>>>();
std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Entity>>> TowerDefense::Combat::s_Adders = std::make_shared<std::vector<std::shared_ptr<TowerDefense::Entity>>>();
std::shared_ptr<std::vector<int>> TowerDefense::Combat::s_Removers = std::make_shared<std::vector<int>>();
std::unique_ptr<std::vector<std::shared_ptr<TowerDefense::Fight>>> TowerDefense::Combat::s_Fights = std::make_unique<std::vector<std::shared_ptr<TowerDefense::Fight>>>();

std::unique_ptr<TowerDefense::TowerInfo> TowerDefense::Combat::s_TowerInfo;
std::unique_ptr<TowerDefense::EnemyInfo> TowerDefense::Combat::s_EnemyInfo;

TowerDefense::Combat::Combat()
	:m_CurrentFight(-1), m_TurnPhase(Phase::START),
	m_StartButton(std::make_unique<Button>(76.0f, 201.0f, 96, 32, "startButton")),
	m_SpeedButton(std::make_unique<Button>(76.0f, 159.0f, 96, 32, "speed1"))
{
}

void TowerDefense::Combat::Render()
{
	Player& player = Player::Get();

	//Board
	Board::Get().Render();

	//Towers, Enemies, Projectiles
	for (unsigned int i = 0; i < s_Entities->size(); i++)
		s_Entities->at(i)->Render();
		

	//Range Indicator
	if (m_SelectedTower)
		m_SelectedTower->GetRangeCircle()->Render();

	//Buttons
	player.RenderDeckButton();
	player.RenderArtifactsPile();
	m_StartButton->Render();
	m_SpeedButton->Render();

	//Stats at top of screen
	player.RenderHealth();
	player.RenderEnergy();
	player.RenderGold();
	player.RenderDay();

	//Render Tower Information
	if (s_TowerInfo)
		s_TowerInfo->Render();

	//Render Enemy Information
	if (s_EnemyInfo)
		s_EnemyInfo->Render();

	//Drawpile, Discardpile, Hand
	RenderCards();
}

void TowerDefense::Combat::Update()
{
	Board::Get().Update();

	UpdateCards();

	UpdateWave();

	Player& player = Player::Get();
	bool deckShow = player.DeckShowing();
	bool drawShow = player.GetDrawPile()->IsShowing();
	bool discardShow = player.GetDiscardPile()->IsShowing();
	bool artifactsShow = player.ArtifactsShowing();
	bool cardDragging = player.GetHand()->DraggingCard();
	bool draggingTowerInfo = DraggingInfo();
	if (!cardDragging && !deckShow && !drawShow && !discardShow && !draggingTowerInfo)
			UpdateButtons();

	if (!deckShow && !drawShow && !discardShow && !artifactsShow)
	{
		if (s_EnemyInfo)
			s_EnemyInfo->Update();
		if (m_SelectedEnemy)
			m_SelectedEnemy->SetSelected(true);
		if (s_TowerInfo)
			s_TowerInfo->Update();
		if (m_SelectedTower)
			m_SelectedTower->SetHighlighted();
	}

	if (!deckShow && !drawShow && !discardShow && !artifactsShow)
		UpdateSelectedEnemy();

	if(!deckShow && !drawShow && !discardShow && !artifactsShow)
		UpdateSelectedTower();

	UpdateEntities();
}

void TowerDefense::Combat::OnSwitch()
{
	//Change Background Color
	Renderer::Get().Clear(237.0f / 255.0f, 225.0f / 255.0f, 190.0f / 255.0f, 1.0f);

	//Reset Combat
	Player& player = Player::Get();
	player.SetEnergy(100);
	player.ResetCardPiles();
	player.GetHand()->ResetSelectedCard();
	m_TurnPhase = Phase::START;

	m_StartButton->SetImages("startButton");
	m_SelectedTower.reset();
	s_TowerInfo.reset();
	m_SelectedEnemy.reset();
	s_EnemyInfo.reset();

	player.ShowDeck(false);
	player.GetDrawPile()->Show(false);
	player.GetDiscardPile()->Show(false);

	player.SetTextColor(0.0f, 0.0f, 0.0f, 1.0f);

	ClearProjectilesAndAnimations();
	ClearTowers();

	player.ArtifactOnFightStart();

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
	s_TowerInfo.reset();
	s_EnemyInfo.reset();
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

	if (player.DeckShowing())
	{
		player.RenderDeck();
		if (!player.GetSelectedDeckCard())
			player.RenderDeckButton();
	}

	if (player.ArtifactsShowing())
	{
		player.RenderArtifacts();
		if (!player.GetSelectedArtifact())
			player.RenderArtifactsPile();
	}
}

//Update All Towers, Projectiles, and Enemies
//Add all new enemies, towers, and projectiles and remove all deleted ones 
void TowerDefense::Combat::UpdateEntities()
{
	//Update Entities
	for (unsigned int i = 0; i < s_Entities->size(); i++)
		s_Entities->at(i)->Update();

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
	bool deckShow = player.DeckShowing();
	bool drawShow = player.GetDrawPile()->IsShowing();
	bool discardShow = player.GetDiscardPile()->IsShowing();
	bool artifactsShow = player.ArtifactsShowing();
	bool cardSelected = player.GetHand()->GetSelectedCard() != -1;
	bool draggingTowerInfo = DraggingInfo();

	if (!cardSelected && !drawShow && !discardShow && !artifactsShow && !draggingTowerInfo)
	{
		if (!player.GetSelectedDeckCard())
		{
			player.UpdateDeckButton();
			if (player.DeckButtonClicked())
				player.ToggleDeckShow();
		}
		player.UpdateDeck();
	}
	if (!cardSelected && !deckShow && !drawShow && !discardShow && !draggingTowerInfo)
		player.UpdateArtifactsPile();
	if (!cardSelected && !deckShow && !discardShow && !artifactsShow && !draggingTowerInfo)
		player.GetDrawPile()->Update();
	if (!cardSelected && !deckShow && !drawShow && !artifactsShow && !draggingTowerInfo)
		player.GetDiscardPile()->Update();
	if (!s_Paused && !deckShow && !drawShow && !artifactsShow && !discardShow && !draggingTowerInfo)
		player.GetHand()->Update();
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
	if (m_TurnPhase == Phase::COMBAT && wave->HasMoreEnemies() && !s_Paused) {
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
				m_StartButton->SetImages("pause");
				ClearProjectilesAndAnimations();
				Player::Get().ArtifactOnRoundStart();
			}
			else if (m_TurnPhase == Phase::COMBAT)
			{
				s_Paused = !s_Paused;
			}
			else if (m_TurnPhase == Phase::END)
			{
				m_TurnPhase = Phase::START;
				Player::Get().DrawHand();
				m_StartButton->SetImages("startButton");
			}
		}
	}

	//Speed Button
	m_SpeedButton->Update();
	if (m_SpeedButton->IsClicked())
	{
		if (s_RoundSpeed == 1) {
			s_RoundSpeed = 2;
			m_SpeedButton->SetImages("speed2");
		}
		else if (s_RoundSpeed == 2) {
			s_RoundSpeed = 3;
			m_SpeedButton->SetImages("speed3");
		}
		else {
			s_RoundSpeed = 1;
			m_SpeedButton->SetImages("speed1");
		}
	}
}

//Find if a tower has been clicked, or deselected
void TowerDefense::Combat::UpdateSelectedTower()
{
	if (Player::Get().GetHand()->DraggingCard())
		return;

	if (Input::GetLeftMouseClicked() && !DraggingInfo())
	{

		bool clickingEnemy = false;
		for (int i = 0; i < (int)s_Entities->size(); i++)
		{
			auto e = s_Entities->at(i);
			if (e->GetEntityType() == Type::ENEMY)
			{
				if (e->Contains(Input::GetMouseX(), Input::GetMouseY()))
				{
					clickingEnemy = true;
					break;
				}
			}
		}

		if ((!m_SelectedTower || !m_SelectedTower->Contains(Input::GetMouseX(), Input::GetMouseY())) && !clickingEnemy)
		{
			m_SelectedTower.reset();
			s_TowerInfo.reset();
		}
	}

	if (m_SelectedTower)
		return;

	for (unsigned int i = 0; i < s_Entities->size(); i++)
	{
		if (s_Entities->at(i)->GetEntityType() == Type::TOWER)
		{
			auto tower = std::dynamic_pointer_cast<Tower::Tower>(s_Entities->at(i));
			if (tower->GetClicked())
			{
				m_SelectedTower = tower;
				if(tower->GetX() < 550)
					s_TowerInfo = std::make_unique<TowerInfo>(tower->GetX() + 130, tower->GetY(), m_SelectedTower);
				else
					s_TowerInfo = std::make_unique<TowerInfo>(tower->GetX() - 130, tower->GetY(), m_SelectedTower);
			}
		}
	}
}

//Find if an enemy has been clicked, or deselected
void TowerDefense::Combat::UpdateSelectedEnemy()
{
	if (m_SelectedEnemy && !GetEntity(m_SelectedEnemy->GetID()))
	{
		m_SelectedEnemy.reset();
		s_EnemyInfo.reset();
	}

	if (Player::Get().GetHand()->DraggingCard())
		return;

	if (Input::GetLeftMouseClicked() && !DraggingInfo())
	{
		bool clickingTower = false;
		for (int i = 0; i < (int)s_Entities->size(); i++)
		{
			auto e = s_Entities->at(i);
			if (e->GetEntityType() == Type::TOWER)
			{
				if (e->Contains(Input::GetMouseX(), Input::GetMouseY()))
				{
					clickingTower = true;
					break;
				}
			}
		}

		if ((!m_SelectedEnemy || !m_SelectedEnemy->Contains(Input::GetMouseX(), Input::GetMouseY())) && !clickingTower)
		{
			m_SelectedEnemy.reset();
			s_EnemyInfo.reset();
		}
	}

	if (m_SelectedEnemy)
		return;

	for (unsigned int i = 0; i < s_Entities->size(); i++)
	{
		if (s_Entities->at(i)->GetEntityType() == Type::ENEMY)
		{
			auto enemy = std::dynamic_pointer_cast<Enemy::Enemy>(s_Entities->at(i));
			if (enemy->GetClicked())
			{
				m_SelectedEnemy = enemy;
				s_EnemyInfo = std::make_unique<EnemyInfo>(225.0f, 560.0f, m_SelectedEnemy);
			}
		}
	}
}

//Triggers all end round properties of towers and switches scene if combat is over
void TowerDefense::Combat::EndRound()
{
	for (unsigned int i = 0; i < s_Entities->size(); i++)
		s_Entities->at(i)->EndRound();

	m_StartButton->SetImages("endButton");

	if (!s_Fights->at(m_CurrentFight)->HasMoreWaves())
	{
		Player::Get().ArtifactOnFightEnd();
		SetScene(SceneType::POSTCOMBAT);
	}
		
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

void TowerDefense::Combat::ClearProjectilesAndAnimations()
{
	for (unsigned int i = 0; i < s_Entities->size(); i++)
	{
		std::shared_ptr<Entity> e = s_Entities->at(i);
		if (e->GetEntityType() == Type::PROJECTILE || e->GetEntityType() == Type::ANIMATION)
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

std::shared_ptr<TowerDefense::Entity> TowerDefense::Combat::GetEntity(unsigned int ID)
{
	for (unsigned int i = 0; i < s_Entities->size(); i++)
	{
		std::shared_ptr<Entity> e = s_Entities->at(i);
		if (e->GetID() == ID)
			return e;
	}
	return nullptr;
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