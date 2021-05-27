#include "pch.h"
#include "Combat.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "core/Board.h"
#include "enemies/Enemies.h"
#include "towers/Archer.h"

int TowerDefense::Combat::s_RoundSpeed = 1;
int TowerDefense::Combat::s_CurrentFight = -1;
bool TowerDefense::Combat::s_Paused = false;

std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Entity>>> TowerDefense::Combat::s_Entities = std::make_shared<std::vector<std::shared_ptr<TowerDefense::Entity>>>();
std::shared_ptr<std::vector<std::shared_ptr<TowerDefense::Entity>>> TowerDefense::Combat::s_Adders = std::make_shared<std::vector<std::shared_ptr<TowerDefense::Entity>>>();
std::shared_ptr<std::vector<int>> TowerDefense::Combat::s_Removers = std::make_shared<std::vector<int>>();
std::unique_ptr<std::vector<std::shared_ptr<TowerDefense::Aura>>> TowerDefense::Combat::s_Auras = std::make_unique <std::vector<std::shared_ptr<TowerDefense::Aura>>>();
std::unique_ptr<std::vector<std::shared_ptr<TowerDefense::Fight>>> TowerDefense::Combat::s_Fights = std::make_unique<std::vector<std::shared_ptr<TowerDefense::Fight>>>();

std::unique_ptr<TowerDefense::TowerInfo> TowerDefense::Combat::s_TowerInfo;
std::unique_ptr<TowerDefense::EnemyInfo> TowerDefense::Combat::s_EnemyInfo;

TowerDefense::Combat::Combat()
	:m_TurnPhase(Phase::START),
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
	m_StartButton->Render();
	m_SpeedButton->Render();

	for (unsigned int i = 0; i < s_Auras->size(); i++)
		s_Auras->at(i)->Render();

	if (!player.DeckShowing() && !player.ArtifactsShowing())
	{
		player.RenderStats();
		player.RenderDeckAndArtifacts();
	}
		
	//Render Tower Information
	if (s_TowerInfo)
		s_TowerInfo->Render();

	//Render Enemy Information
	if (s_EnemyInfo)
		s_EnemyInfo->Render();

	//Drawpile, Discardpile, Hand
	RenderCards();

	if (player.DeckShowing() || player.ArtifactsShowing())
	{
		player.RenderStats();
		player.RenderDeckAndArtifacts();
	}
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
	bool cardDragging = player.GetHand()->DraggingCard() || player.GetHand()->SelectingCards();
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

	UpdateAuras();
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

	ClearProjectilesAndAnimationsAndEnemies();
	ClearTowers();
	s_Auras->clear();

	player.ArtifactOnFightStart();

	s_CurrentFight++;
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
	s_Auras.reset();
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

void TowerDefense::Combat::UpdateAuras()
{
	for (unsigned int i = 0; i < s_Auras->size(); i++)
		s_Auras->at(i)->Update();
}

//Updates Hand, Draw pile, Discard pile, and View Deck button
void TowerDefense::Combat::UpdateCards()
{
	Player& player = Player::Get();
	bool deckShow = player.DeckShowing();
	bool drawShow = player.GetDrawPile()->IsShowing();
	bool discardShow = player.GetDiscardPile()->IsShowing();
	bool artifactsShow = player.ArtifactsShowing();
	bool cardSelected = player.GetHand()->GetSelectedCard() != -1 || player.GetHand()->SelectingCards();
	bool draggingInfo = DraggingInfo();

	if (!cardSelected && !drawShow && !discardShow && !draggingInfo)
		player.UpdateDeckAndArtifacts();
	if (!cardSelected && !deckShow && !discardShow && !artifactsShow && !draggingInfo)
		player.GetDrawPile()->Update();
	if (!cardSelected && !deckShow && !drawShow && !artifactsShow && !draggingInfo)
		player.GetDiscardPile()->Update();
	if (!s_Paused && !deckShow && !drawShow && !artifactsShow && !discardShow && !draggingInfo)
		player.GetHand()->Update();
}

void TowerDefense::Combat::UpdateWave()
{
	//Check if wave is over and End Round
	auto wave = s_Fights->at(s_CurrentFight)->GetWave();
	if (m_TurnPhase == Phase::COMBAT && (!wave || !wave->HasMoreEnemies()) && EnemiesDefeated())
	{
		m_TurnPhase = Phase::END;
		EndRound();
	}

	//Add new Enemies from wave
	if (m_TurnPhase == Phase::COMBAT && wave->HasMoreEnemies() && !s_Paused) {
		std::shared_ptr<Enemy::Enemy> e = s_Fights->at(s_CurrentFight)->GetWave()->GetNextEnemy();
		if (e)
			AddEntity(e);
	}
}

//Check if start and speed buttons are clicked 
void TowerDefense::Combat::UpdateButtons()
{
	//Start Button
	if (s_Fights->at(s_CurrentFight)->HasMoreWaves() || m_TurnPhase != Phase::START)
	{
		m_StartButton->Update();
		if (m_StartButton->IsClicked())
		{
			if (m_TurnPhase == Phase::START)
			{
				s_Fights->at(s_CurrentFight)->NextWave();
				m_TurnPhase = Phase::COMBAT;
				m_StartButton->SetImages("pause");
				ClearProjectilesAndAnimationsAndEnemies();
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
				s_EnemyInfo = std::make_unique<EnemyInfo>(225.0f, 500.0f, m_SelectedEnemy);
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

	if (!s_Fights->at(s_CurrentFight)->HasMoreWaves())
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

void TowerDefense::Combat::ClearProjectilesAndAnimationsAndEnemies()
{
	for (unsigned int i = 0; i < s_Entities->size(); i++)
	{
		std::shared_ptr<Entity> e = s_Entities->at(i);
		auto type = e->GetEntityType();
		if (type == Type::PROJECTILE || type == Type::ANIMATION || type == Type::ENEMY)
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

	auto hand = Player::Get().GetHand();
	for (int i = 0; i < hand->GetSize(); i++)
	{
		if (hand->GetCard(i)->GetID() == ID)
			return hand->GetCard(i);
	}

	auto artifacts = Player::Get().GetArtifacts();
	for (int i = 0; i < artifacts->GetSize(); i++)
	{
		if (artifacts->GetArtifact(i)->GetID() == ID)
			return artifacts->GetArtifact(i);
	}

	for (unsigned int i = 0; i < s_Auras->size(); i++)
	{
		if (s_Auras->at(i)->GetID() == ID)
			return s_Auras->at(i);
	}

	return nullptr;
}

void TowerDefense::Combat::AddAura(std::shared_ptr<Aura> a)
{
	a->OnAquire();
	a->SetX(150.0f + s_Auras->size() * 50);
	a->SetY(200.0f);
	s_Auras->push_back(a);
}

void TowerDefense::Combat::OnCardPlayAuras(std::shared_ptr<Card> c)
{
	for (unsigned int i = 0; i < s_Auras->size(); i++)
		s_Auras->at(i)->OnCardPlay(c);
}

void TowerDefense::Combat::OnEnemyHit(unsigned int id, std::shared_ptr<Entity> source, Tower::DamageType type)
{
	auto e = std::dynamic_pointer_cast<Enemy::Enemy>(GetEntity(id));
	for (unsigned int i = 0; i < s_Auras->size(); i++)
		s_Auras->at(i)->OnEnemyHit(e, source, type);
}

void TowerDefense::Combat::OnEnemyDeath(unsigned int id)
{
	auto e = std::dynamic_pointer_cast<Enemy::Enemy>(GetEntity(id));
	for (unsigned int i = 0; i < s_Auras->size(); i++)
		s_Auras->at(i)->OnEnemyDeath(e);
}

//Create pools of difficulty for different fights and randomly select fights from the appropriate pools to fill up the s_Fights vector for the run
//Should be called once at the beginning of a run to generate the set of combats
void TowerDefense::Combat::GenerateFights()
{
	s_CurrentFight = -1;
	s_Fights = std::make_unique<std::vector<std::shared_ptr<TowerDefense::Fight>>>();

	//day 1-3 fights
	std::vector<std::shared_ptr<Fight>> pool1;
	//Rats
	auto waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies1[] = { 0, 0, 0, 200, 0, 200, 0, 200 };
	waves->push_back(std::make_shared<Wave>(enemies1, 8));
	pool1.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies2[] = { 5, 0, 5, 100, 5, 100, 5, 100 , 5, 100, 5, 100, 5, 100, 5, 100};
	waves->push_back(std::make_shared<Wave>(enemies2, 16));
	pool1.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies3[] = { 6, 0, 6, 250, 6, 250 };
	waves->push_back(std::make_shared<Wave>(enemies3, 6));
	pool1.push_back(std::make_shared<Fight>(waves));

	//day 4-6 fights
	std::vector<std::shared_ptr<Fight>> pool2;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies4[] = { 0, 0, 0, 100, 0, 100, 0, 100, 0, 100 };
	const int enemies5[] = { 0, 0, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50, 0, 50 };
	const int enemies6[] = { 0, 0, 0, 50, 0, 50, 1, 150 };
	waves->push_back(std::make_shared<Wave>(enemies4, 10));
	waves->push_back(std::make_shared<Wave>(enemies5, 14));
	waves->push_back(std::make_shared<Wave>(enemies6, 8));
	pool2.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies7[] = { 6, 0, 6, 150, 6, 150, 6, 150, 6, 150 };
	const int enemies8[] = { 6, 0, 6, 100, 6, 100, 6, 100, 6, 100, 6, 100, 6, 100, 6, 100, 6, 100 };
	const int enemies9[] = { 6, 0, 6, 100, 6, 100, 9, 200, 9, 50 };
	waves->push_back(std::make_shared<Wave>(enemies7, 10));
	waves->push_back(std::make_shared<Wave>(enemies8, 18));
	waves->push_back(std::make_shared<Wave>(enemies9, 10));
	pool2.push_back(std::make_shared<Fight>(waves));
	
	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies10[] = { 5, 0, 5, 50, 5, 50, 5, 50, 5, 50, 5, 50, 5, 50, 5, 50 };
	const int enemies11[] = { 5, 0, 5, 20, 5, 20, 5, 20, 5, 20, 5, 20, 5, 20 };
	const int enemies12[] = { 5, 0, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 7, 150, 7, 30 , 7, 30 };
	waves->push_back(std::make_shared<Wave>(enemies10, 16));
	waves->push_back(std::make_shared<Wave>(enemies11, 14));
	waves->push_back(std::make_shared<Wave>(enemies12, 26));
	pool2.push_back(std::make_shared<Fight>(waves));

	//day 7-9 fights
	std::vector<std::shared_ptr<Fight>> pool3;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies13[] = { 2, 0, 2, 200, 2, 200, 2, 200 };
	const int enemies14[] = { 2, 0, 2, 100, 2, 100, 2, 100, 2, 100 };
	const int enemies15[] = { 2, 0, 2, 50, 2, 50, 3, 150, 3, 150 };
	waves->push_back(std::make_shared<Wave>(enemies13, 8));
	waves->push_back(std::make_shared<Wave>(enemies14, 10));
	waves->push_back(std::make_shared<Wave>(enemies15, 10));
	pool3.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies16[] = { 6, 0, 6, 100, 6, 100, 6, 100, 6, 100 };
	const int enemies17[] = { 6, 0, 6, 100, 6, 100, 6, 100, 6, 100, 9, 100, 9, 100 , 9, 100 , 9, 100 };
	const int enemies18[] = { 10, 0 };
	waves->push_back(std::make_shared<Wave>(enemies16, 10));
	waves->push_back(std::make_shared<Wave>(enemies17, 18));
	waves->push_back(std::make_shared<Wave>(enemies18, 2));
	pool3.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies19[] = { 7, 0, 7, 100, 7, 100, 7, 100};
	const int enemies20[] = { 7, 0, 7, 50, 7, 50, 7, 50, 7, 50, 7, 50, 7, 50, 7, 50, 7, 50, 7, 50 };
	const int enemies21[] = { 7, 0, 7, 20, 7, 20, 7, 20, 7, 20, 8, 150, 8, 150, 8, 150, 8, 150, 8, 150 };
	waves->push_back(std::make_shared<Wave>(enemies19, 8));
	waves->push_back(std::make_shared<Wave>(enemies20, 20));
	waves->push_back(std::make_shared<Wave>(enemies21, 20));
	pool3.push_back(std::make_shared<Fight>(waves));

	//day 10 fights
	std::vector<std::shared_ptr<Fight>> pool4;
	//Rats
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

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies32[] = { 6, 0, 6, 100, 6, 100, 6, 100, 6, 100 };
	const int enemies33[] = { 6, 0, 6, 60, 6, 60, 6, 60, 6, 60, 6, 60, 6, 60 };
	const int enemies34[] = { 6, 0, 6, 50, 6, 50, 9, 50 };
	const int enemies35[] = { 6, 0, 6, 50, 6, 50, 6, 50, 6, 50, 9, 150, 9, 150, 9, 150 };
	const int enemies36[] = { 9, 0, 9, 100, 9, 100, 9, 100, 9, 100 };
	const int enemies37[] = { 9, 0, 9, 100, 9, 100, 11, 150, 11, 100 };
	const int enemies38[] = { 10, 0 };
	const int enemies39[] = { 6, 0, 6, 50, 6, 50, 6, 50, 9, 100, 9, 100, 9, 100, 11, 150, 11, 150, 11, 150 };
	const int enemies40[] = { 11, 0, 11, 75, 11, 75, 9, 50, 9, 50, 9, 50, 9, 50, 11, 75, 11, 75, 11, 75 };
	const int enemies41[] = { 10, 0 , 10, 150};
	waves->push_back(std::make_shared<Wave>(enemies32, 10));
	waves->push_back(std::make_shared<Wave>(enemies33, 14));
	waves->push_back(std::make_shared<Wave>(enemies34, 8));
	waves->push_back(std::make_shared<Wave>(enemies35, 16));
	waves->push_back(std::make_shared<Wave>(enemies36, 10));
	waves->push_back(std::make_shared<Wave>(enemies37, 10));
	waves->push_back(std::make_shared<Wave>(enemies38, 2));
	waves->push_back(std::make_shared<Wave>(enemies39, 20));
	waves->push_back(std::make_shared<Wave>(enemies40, 20));
	waves->push_back(std::make_shared<Wave>(enemies41, 4));
	pool4.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies42[] = { 5, 0, 5, 50, 5, 50, 5, 50, 5, 50, 5, 50, 5, 50 };
	const int enemies43[] = { 5, 0, 5, 50, 5, 50, 5, 50, 5, 50, 5, 50, 7, 150, 7, 150, 7, 150 };
	const int enemies44[] = { 5, 0, 5, 150, 5, 150, 5, 150, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10 };
	const int enemies45[] = { 7, 0, 7, 100, 7, 100, 7, 100, 7, 100, 7, 100 };
	const int enemies46[] = { 7, 0, 7, 100, 7, 100, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 7, 100, 7, 100, 7, 100, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 7, 100, 7, 100, 7, 100 };
	const int enemies47[] = { 7, 0, 7, 100, 7, 100, 8, 100, 8, 100 };
	const int enemies48[] = { 8, 0, 8, 50, 8, 50, 8, 50, 8, 50, 8, 50, 8, 50 };
	const int enemies49[] = { 8, 0, 8, 100, 8, 100, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 8, 100, 8, 100, 8, 100, 5, 10, 5, 10, 5, 10, 5, 10, 5, 10, 8, 100, 8, 100, 8, 100 };
	const int enemies50[] = { 8, 0, 8, 100, 7, 20, 7, 20, 7, 20, 8, 100, 8, 100, 7, 20, 7, 20, 7, 20, 8, 100, 8, 100 };
	const int enemies51[] = { 19, 0 };
	waves->push_back(std::make_shared<Wave>(enemies42, 14));
	waves->push_back(std::make_shared<Wave>(enemies43, 18));
	waves->push_back(std::make_shared<Wave>(enemies44, 34));
	waves->push_back(std::make_shared<Wave>(enemies45, 12));
	waves->push_back(std::make_shared<Wave>(enemies46, 38));
	waves->push_back(std::make_shared<Wave>(enemies47, 10));
	waves->push_back(std::make_shared<Wave>(enemies48, 14));
	waves->push_back(std::make_shared<Wave>(enemies49, 38));
	waves->push_back(std::make_shared<Wave>(enemies50, 24));
	waves->push_back(std::make_shared<Wave>(enemies51, 2));
	pool4.push_back(std::make_shared<Fight>(waves));

	//Days 11-13
	std::vector<std::shared_ptr<Fight>> pool5;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies52[] = { 0, 0, 0, 30, 0, 30, 0, 30, 0, 30, 1, 100, 1, 100, 14, 100 };
	const int enemies53[] = { 14, 0, 14, 50, 14, 50, 14, 50, 14, 50 };
	const int enemies54[] = { 14, 0, 14, 30, 15, 30, 14, 30, 14, 30 };
	waves->push_back(std::make_shared<Wave>(enemies52, 16));
	waves->push_back(std::make_shared<Wave>(enemies53, 10));
	waves->push_back(std::make_shared<Wave>(enemies54, 10));
	pool5.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies55[] = { 12, 0, 12, 150, 12, 200, 12, 200, 9, 200 };
	const int enemies56[] = { 12, 0, 12, 50, 12, 50, 12, 50, 12, 50 };
	const int enemies57[] = { 12, 0, 12, 50, 12, 50, 11, 150, 11, 150 };
	waves->push_back(std::make_shared<Wave>(enemies55, 10));
	waves->push_back(std::make_shared<Wave>(enemies56, 10));
	waves->push_back(std::make_shared<Wave>(enemies57, 10));
	pool5.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies58[] = { 17, 0, 17, 200, 17, 200};
	const int enemies59[] = { 8, 0, 17, 100, 17, 50, 8, 100, 8, 100 };
	const int enemies60[] = { 17, 0, 17, 50, 17, 50, 17, 50, 17, 50, 17, 50, 17, 50 };
	waves->push_back(std::make_shared<Wave>(enemies58, 6));
	waves->push_back(std::make_shared<Wave>(enemies59, 10));
	waves->push_back(std::make_shared<Wave>(enemies60, 14));
	pool5.push_back(std::make_shared<Fight>(waves));

	//Days 14-16
	std::vector<std::shared_ptr<Fight>> pool6;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies61[] = { 1, 0, 1, 100, 1, 100, 15, 100, 15, 100, 1, 100, 1, 100, 1, 100};
	const int enemies62[] = { 14, 0, 14, 100, 15, 100, 15, 50, 15, 50, 14, 100, 14, 100 };
	const int enemies63[] = { 14, 0, 14, 50, 16, 50, 16, 50, 14, 50, 14, 50, 15, 50, 15, 50, 14, 50, 14, 50 };
	waves->push_back(std::make_shared<Wave>(enemies61, 16));
	waves->push_back(std::make_shared<Wave>(enemies62, 14));
	waves->push_back(std::make_shared<Wave>(enemies63, 20));
	pool6.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies64[] = { 11, 0, 11, 150, 11, 200, 9, 200, 9, 200 };
	const int enemies65[] = { 11, 0, 11, 100, 11, 100, 11, 100, 11, 100, 13, 100, 13, 100 };
	const int enemies66[] = { 9, 0, 9, 50, 9, 50, 13, 150, 13, 150 };
	waves->push_back(std::make_shared<Wave>(enemies64, 10));
	waves->push_back(std::make_shared<Wave>(enemies65, 14));
	waves->push_back(std::make_shared<Wave>(enemies66, 10));
	pool6.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies67[] = { 17, 0, 17, 200, 17, 200, 18, 200};
	const int enemies68[] = { 8, 0, 17, 100, 17, 50, 18, 100, 18, 100 };
	const int enemies69[] = { 8, 0, 8, 50, 17, 50, 17, 50, 18, 50, 18, 50, 18, 50 };
	waves->push_back(std::make_shared<Wave>(enemies67, 8));
	waves->push_back(std::make_shared<Wave>(enemies68, 10));
	waves->push_back(std::make_shared<Wave>(enemies69, 14));
	pool6.push_back(std::make_shared<Fight>(waves));

	//Days 17-19
	std::vector<std::shared_ptr<Fight>> pool7;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies70[] = { 1, 0, 1, 100, 1, 100, 15, 100, 15, 100, 1, 100, 1, 100, 1, 100 };
	const int enemies71[] = { 14, 0, 14, 100, 15, 100, 15, 50, 15, 50, 14, 100, 14, 100 };
	const int enemies72[] = { 14, 0, 14, 50, 16, 50, 16, 50, 14, 50, 14, 50, 15, 50, 15, 50, 14, 50, 14, 50 };
	waves->push_back(std::make_shared<Wave>(enemies70, 16));
	waves->push_back(std::make_shared<Wave>(enemies71, 14));
	waves->push_back(std::make_shared<Wave>(enemies72, 20));
	pool7.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies73[] = { 11, 0, 11, 150, 11, 200, 9, 200, 9, 200 };
	const int enemies74[] = { 11, 0, 11, 50, 11, 50, 11, 50, 11, 50, 11, 50, 11, 50, 11, 50, 13, 50, 13, 50 };
	const int enemies75[] = { 9, 0, 9, 50, 9, 50, 13, 150, 13, 150 };
	waves->push_back(std::make_shared<Wave>(enemies73, 10));
	waves->push_back(std::make_shared<Wave>(enemies74, 20));
	waves->push_back(std::make_shared<Wave>(enemies75, 10));
	pool7.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies76[] = { 17, 0, 17, 200, 17, 200, 18, 200 };
	const int enemies77[] = { 8, 0, 17, 100, 17, 50, 18, 100, 18, 100 };
	const int enemies78[] = { 8, 0, 8, 50, 17, 50, 17, 50, 18, 50, 18, 50, 18, 50 };
	waves->push_back(std::make_shared<Wave>(enemies76, 8));
	waves->push_back(std::make_shared<Wave>(enemies77, 10));
	waves->push_back(std::make_shared<Wave>(enemies78, 14));
	pool7.push_back(std::make_shared<Fight>(waves));

	//Day 20
	std::vector<std::shared_ptr<Fight>> pool8;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies79[] = { 0, 0, 0, 30, 0, 30, 0, 30, 1, 150, 1, 150, 1, 150, 1, 150 };
	const int enemies80[] = { 1, 0, 1, 100, 1, 100, 1, 100, 1, 100, 14, 150, 14, 150, 14, 150 };
	const int enemies81[] = { 0, 0, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20, 0, 20 };
	const int enemies82[] = { 1, 0, 1, 50, 1, 50, 1, 50, 1, 50, 1, 50, 1, 50, 1, 50 };
	const int enemies83[] = { 14, 0, 14, 100, 14, 100, 14, 100, 15, 100, 15, 100, 15, 100 };
	const int enemies84[] = { 14, 0, 14, 100, 16, 100, 16, 100, 14, 100, 14, 100, 15, 100, 15, 100, 14, 100, 14, 100 };
	const int enemies85[] = { 4, 0, 4, 300 };
	const int enemies86[] = { 14, 0, 14, 100, 14, 100, 4, 100, 16, 50, 16, 50, 15, 50, 15, 50 };
	const int enemies87[] = { 4, 0, 4, 100, 15, 50, 15, 50, 15, 50, 16, 50, 16, 50, 16, 50 };
	const int enemies88[] = { 4, 0, 4, 100, 4, 100, 4, 100, 4, 100 };
	waves->push_back(std::make_shared<Wave>(enemies79, 16));
	waves->push_back(std::make_shared<Wave>(enemies80, 16));
	waves->push_back(std::make_shared<Wave>(enemies81, 40));
	waves->push_back(std::make_shared<Wave>(enemies82, 16));
	waves->push_back(std::make_shared<Wave>(enemies83, 14));
	waves->push_back(std::make_shared<Wave>(enemies84, 20));
	waves->push_back(std::make_shared<Wave>(enemies85, 4));
	waves->push_back(std::make_shared<Wave>(enemies86, 16));
	waves->push_back(std::make_shared<Wave>(enemies87, 16));
	waves->push_back(std::make_shared<Wave>(enemies88, 10));
	pool8.push_back(std::make_shared<Fight>(waves));

	//determine combats from random pool
	int fight = (int)(Random::GetFloat()* pool1.size());
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

	fight = (int)(Random::GetFloat() * pool5.size());
	s_Fights->push_back(pool5[fight]);
	pool5.erase(pool5.begin() + fight);

	fight = (int)(Random::GetFloat() * pool5.size());
	s_Fights->push_back(pool5[fight]);
	pool5.erase(pool5.begin() + fight);

	fight = (int)(Random::GetFloat() * pool5.size());
	s_Fights->push_back(pool5[fight]);
	pool5.erase(pool5.begin() + fight);

	fight = (int)(Random::GetFloat() * pool6.size());
	s_Fights->push_back(pool6[fight]);
	pool6.erase(pool6.begin() + fight);

	fight = (int)(Random::GetFloat() * pool6.size());
	s_Fights->push_back(pool6[fight]);
	pool6.erase(pool6.begin() + fight);

	fight = (int)(Random::GetFloat() * pool6.size());
	s_Fights->push_back(pool6[fight]);
	pool6.erase(pool6.begin() + fight);

	fight = (int)(Random::GetFloat() * pool7.size());
	s_Fights->push_back(pool7[fight]);
	pool7.erase(pool7.begin() + fight);

	fight = (int)(Random::GetFloat() * pool7.size());
	s_Fights->push_back(pool7[fight]);
	pool7.erase(pool7.begin() + fight);

	fight = (int)(Random::GetFloat() * pool7.size());
	s_Fights->push_back(pool7[fight]);
	pool7.erase(pool7.begin() + fight);

	fight = (int)(Random::GetFloat() * pool8.size());
	s_Fights->push_back(pool8[fight]);
	pool8.erase(pool8.begin() + fight);
}