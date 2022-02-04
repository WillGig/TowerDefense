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
std::unique_ptr<std::vector<std::shared_ptr<TowerDefense::Aura::Aura>>> TowerDefense::Combat::s_Auras = std::make_unique <std::vector<std::shared_ptr<TowerDefense::Aura::Aura>>>();
std::unique_ptr<std::vector<std::shared_ptr<TowerDefense::Fight>>> TowerDefense::Combat::s_Fights = std::make_unique<std::vector<std::shared_ptr<TowerDefense::Fight>>>();

std::unique_ptr<TowerDefense::TowerInfo> TowerDefense::Combat::s_TowerInfo;
std::unique_ptr<TowerDefense::EnemyInfo> TowerDefense::Combat::s_EnemyInfo;

std::vector<int> TowerDefense::Combat::s_FightOrder;

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

	m_WaveNumber->Render();

	for (unsigned int i = 0; i < s_Auras->size(); i++)
		s_Auras->at(i)->Render();

	player.ArtifactCombatRender();

	if (!player.DeckShowing() && !player.ArtifactsShowing())
	{
		player.RenderStats();
		player.RenderDeckAndArtifacts();
	}

	InGameSettings::Get().RenderButton();
		
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

	//Settings Menu
	if (InGameSettings::Get().IsShowing())
		InGameSettings::Get().Render();
}

void TowerDefense::Combat::Update()
{
	if (InGameSettings::Get().IsShowing())
	{
		InGameSettings::Get().Update();
		return;
	}

	Board::Get().Update();

	UpdateWave();

	UpdateCards();

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

		UpdateSelectedEnemy();

		UpdateSelectedTower();

		player.ArtifactCombatUpdate();
	}

	UpdateEntities();

	UpdateAuras();
}

void TowerDefense::Combat::OnSwitch()
{
	//Switch Board
	Board::Get().LoadRandomMap();

	InGameSettings::Get().Show(false);

	//Change Background Color
	Renderer::Get().Clear(237.0f / 255.0f, 225.0f / 255.0f, 190.0f / 255.0f, 1.0f);

	//Reset Combat
	Player& player = Player::Get();
	player.SetEnergy(100);
	player.ResetCardPiles();
	player.GetHand()->ResetSelectedCard();
	player.GetHand()->ResetDiscardCard();
	m_TurnPhase = Phase::START;

	m_StartButton->SetImages("startButton");
	m_WaveNumber = std::make_unique<Text>("Wave: 1/" + 
		std::to_string(s_Fights->at(s_CurrentFight + 1)->GetNumberOfWaves()), 76.0f, 120.0f, 14.0f, 0.0f);

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

	player.ApplyAuras();
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
	if (!cardSelected && !deckShow && !drawShow && !discardShow && !artifactsShow && !draggingInfo)
	{
		InGameSettings::Get().UpdateButton();
	}
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
		{
			e->MoveToStart();
			AddEntity(e);
		}
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
				auto fight = s_Fights->at(s_CurrentFight);
				m_WaveNumber = std::make_unique<Text>("Wave: " + std::to_string(fight->GetCurrentWave() + 2) + "/"
					+ std::to_string(fight->GetNumberOfWaves()), 76.0f, 120.0f, 14.0f, 0.0f);
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

		if ((!m_SelectedTower || (!m_SelectedTower->Contains(Input::GetMouseX(), Input::GetMouseY())) && !clickingEnemy && !s_TowerInfo->Upgrading()))
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

	if (hand->GetCurrentPlayingCard() && hand->GetCurrentPlayingCard()->GetID() == ID)
		return hand->GetCurrentPlayingCard();

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

void TowerDefense::Combat::AddAura(std::shared_ptr<Aura::Aura> a)
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

//Generates a random seed of fights and sends it to the GenerateFightsFromRandomOrder function
//Should be called once at the beginning of a run to generate the set of combats
void TowerDefense::Combat::GenerateFights()
{
	std::vector<int> fightOrder(30);

	std::vector<int> pool1{ 0,1,2 };
	std::vector<int> pool2{ 0,1,2 };
	std::vector<int> pool3{ 0,1,2 };
	std::vector<int> pool4{ 0,1,2 };
	std::vector<int> pool5{ 0,1,2 };
	std::vector<int> pool6{ 0,1,2 };
	std::vector<int> pool7{ 0,1,2 };
	std::vector<int> pool8{ 0,1,2 };
	std::vector<int> pool9{ 0,1,2 };
	std::vector<int> pool10{ 0,1,2 };
	std::vector<int> pool11{ 0,1,2 };
	std::vector<int> pool12{ 0,1,2 };


	int fight = (int)(Random::GetFloat() * pool1.size());
	fightOrder[0] = pool1[fight];
	pool1.erase(pool1.begin() + fight);

	fight = (int)(Random::GetFloat() * pool1.size());
	fightOrder[1] = pool1[fight];
	pool1.erase(pool1.begin() + fight);

	fight = (int)(Random::GetFloat() * pool1.size());
	fightOrder[2] = pool1[fight];
	pool1.erase(pool1.begin() + fight);

	fight = (int)(Random::GetFloat() * pool2.size());
	fightOrder[3] = pool2[fight];
	pool2.erase(pool2.begin() + fight);

	fight = (int)(Random::GetFloat() * pool2.size());
	fightOrder[4] = pool2[fight];
	pool2.erase(pool2.begin() + fight);

	fight = (int)(Random::GetFloat() * pool2.size());
	fightOrder[5] = pool2[fight];
	pool2.erase(pool2.begin() + fight);

	fight = (int)(Random::GetFloat() * pool3.size());
	fightOrder[6] = pool3[fight];
	pool3.erase(pool3.begin() + fight);

	fight = (int)(Random::GetFloat() * pool3.size());
	fightOrder[7] = pool3[fight];
	pool3.erase(pool3.begin() + fight);

	fight = (int)(Random::GetFloat() * pool3.size());
	fightOrder[8] = pool3[fight];
	pool3.erase(pool3.begin() + fight);

	fight = (int)(Random::GetFloat() * pool4.size());
	fightOrder[9] = pool4[fight];
	pool4.erase(pool4.begin() + fight);

	fight = (int)(Random::GetFloat() * pool5.size());
	fightOrder[10] = pool5[fight];
	pool5.erase(pool5.begin() + fight);

	fight = (int)(Random::GetFloat() * pool5.size());
	fightOrder[11] = pool5[fight];
	pool5.erase(pool5.begin() + fight);

	fight = (int)(Random::GetFloat() * pool5.size());
	fightOrder[12] = pool5[fight];
	pool5.erase(pool5.begin() + fight);

	fight = (int)(Random::GetFloat() * pool6.size());
	fightOrder[13] = pool6[fight];
	pool6.erase(pool6.begin() + fight);

	fight = (int)(Random::GetFloat() * pool6.size());
	fightOrder[14] = pool6[fight];
	pool6.erase(pool6.begin() + fight);

	fight = (int)(Random::GetFloat() * pool6.size());
	fightOrder[15] = pool6[fight];
	pool6.erase(pool6.begin() + fight);

	fight = (int)(Random::GetFloat() * pool7.size());
	fightOrder[16] = pool7[fight];
	pool7.erase(pool7.begin() + fight);

	fight = (int)(Random::GetFloat() * pool7.size());
	fightOrder[17] = pool7[fight];
	pool7.erase(pool7.begin() + fight);

	fight = (int)(Random::GetFloat() * pool7.size());
	fightOrder[18] = pool7[fight];
	pool7.erase(pool7.begin() + fight);

	fight = (int)(Random::GetFloat() * pool8.size());
	fightOrder[19] = pool8[fight];
	pool8.erase(pool8.begin() + fight);

	fight = (int)(Random::GetFloat() * pool9.size());
	fightOrder[20] = pool9[fight];
	pool9.erase(pool9.begin() + fight);

	fight = (int)(Random::GetFloat() * pool9.size());
	fightOrder[21] = pool9[fight];
	pool9.erase(pool9.begin() + fight);

	fight = (int)(Random::GetFloat() * pool9.size());
	fightOrder[22] = pool9[fight];
	pool9.erase(pool9.begin() + fight);

	fight = (int)(Random::GetFloat() * pool10.size());
	fightOrder[23] = pool10[fight];
	pool10.erase(pool10.begin() + fight);

	fight = (int)(Random::GetFloat() * pool10.size());
	fightOrder[24] = pool10[fight];
	pool10.erase(pool10.begin() + fight);

	fight = (int)(Random::GetFloat() * pool10.size());
	fightOrder[25] = pool10[fight];
	pool10.erase(pool10.begin() + fight);

	fight = (int)(Random::GetFloat() * pool11.size());
	fightOrder[26] = pool11[fight];
	pool11.erase(pool11.begin() + fight);

	fight = (int)(Random::GetFloat() * pool11.size());
	fightOrder[27] = pool11[fight];
	pool11.erase(pool11.begin() + fight);

	fight = (int)(Random::GetFloat() * pool11.size());
	fightOrder[28] = pool11[fight];
	pool11.erase(pool11.begin() + fight);

	fight = (int)(Random::GetFloat() * pool12.size());
	fightOrder[29] = pool12[fight];
	pool12.erase(pool12.begin() + fight);

	GenerateFightsFromOrder(fightOrder);
}

//Create pools of difficulty for different fights and fills up the s_Fights vector for the run according 
//to the fightOrder array
void TowerDefense::Combat::GenerateFightsFromOrder(std::vector<int> fightOrder)
{
	s_FightOrder = fightOrder;

	s_CurrentFight = -1;
	s_Fights = std::make_unique<std::vector<std::shared_ptr<TowerDefense::Fight>>>();

	using namespace Enemy;

	//day 1-3 fights
	std::vector<std::shared_ptr<Fight>> pool1;
	//Rats
	auto waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies1[] = { RAT, 0, RAT, 200, RAT, 200, RAT, 200 };
	waves->push_back(std::make_shared<Wave>(enemies1, 8));
	pool1.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies2[] = { BEETLE, 0, BEETLE, 100, BEETLE, 100, BEETLE, 100 , BEETLE, 100, BEETLE, 100, BEETLE, 100, BEETLE, 100};
	waves->push_back(std::make_shared<Wave>(enemies2, 16));
	pool1.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies3[] = { SLIME, 0, SLIME, 250, SLIME, 250 };
	waves->push_back(std::make_shared<Wave>(enemies3, 6));
	pool1.push_back(std::make_shared<Fight>(waves));

	//day 4-6 fights
	std::vector<std::shared_ptr<Fight>> pool2;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies4[] = { RAT, 0, RAT, 100, RAT, 100, RAT, 100, RAT, 100 };
	const int enemies5[] = { RAT, 0, RAT, 50, RAT, 50, RAT, 50, RAT, 50, RAT, 50, RAT, 50 };
	const int enemies6[] = { RAT, 0, RAT, 50, RAT, 50, GIANTRAT, 150 };
	waves->push_back(std::make_shared<Wave>(enemies4, 10));
	waves->push_back(std::make_shared<Wave>(enemies5, 14));
	waves->push_back(std::make_shared<Wave>(enemies6, 8));
	pool2.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies7[] = { SLIME, 0, SLIME, 150, SLIME, 150, SLIME, 150, SLIME, 150 };
	const int enemies8[] = { SLIME, 0, SLIME, 100, SLIME, 100, SLIME, 100, SLIME, 100, SLIME, 100, SLIME, 100, SLIME, 100, SLIME, 100 };
	const int enemies9[] = { SLIME, 0, SLIME, 100, SLIME, 100, BLOB, 200, BLOB, 50 };
	waves->push_back(std::make_shared<Wave>(enemies7, 10));
	waves->push_back(std::make_shared<Wave>(enemies8, 18));
	waves->push_back(std::make_shared<Wave>(enemies9, 10));
	pool2.push_back(std::make_shared<Fight>(waves));
	
	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies10[] = { BEETLE, 0, BEETLE, 50, BEETLE, 50, BEETLE, 50, BEETLE, 50, BEETLE, 50, BEETLE, 50, BEETLE, 50 };
	const int enemies11[] = { BEETLE, 0, BEETLE, 20, BEETLE, 20, BEETLE, 20, BEETLE, 20, BEETLE, 20, BEETLE, 20 };
	const int enemies12[] = { BEETLE, 0, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, SPIDER, 150, SPIDER, 30 , SPIDER, 30 };
	waves->push_back(std::make_shared<Wave>(enemies10, 16));
	waves->push_back(std::make_shared<Wave>(enemies11, 14));
	waves->push_back(std::make_shared<Wave>(enemies12, 26));
	pool2.push_back(std::make_shared<Fight>(waves));

	//day 7-9 fights
	std::vector<std::shared_ptr<Fight>> pool3;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies13[] = { GOBLIN, 0, GOBLIN, 200, GOBLIN, 200, GOBLIN, 200 };
	const int enemies14[] = { GOBLIN, 0, GOBLIN, 100, GOBLIN, 100, 2, 100, GOBLIN, 100 };
	const int enemies15[] = { GOBLIN, 0, GOBLIN, 50, GOBLIN, 50, ORC, 150, ORC, 150 };
	waves->push_back(std::make_shared<Wave>(enemies13, 8));
	waves->push_back(std::make_shared<Wave>(enemies14, 10));
	waves->push_back(std::make_shared<Wave>(enemies15, 10));
	pool3.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies16[] = { SLIME, 0, SLIME, 100, SLIME, 100, SLIME, 100, SLIME, 100 };
	const int enemies17[] = { SLIME, 0, SLIME, 100, SLIME, 100, SLIME, 100, SLIME, 100, BLOB, 100, BLOB, 100 , BLOB, 100 , BLOB, 100 };
	const int enemies18[] = { OOZE, 0, OOZE, 120};
	waves->push_back(std::make_shared<Wave>(enemies16, 10));
	waves->push_back(std::make_shared<Wave>(enemies17, 18));
	waves->push_back(std::make_shared<Wave>(enemies18, 4));
	pool3.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies19[] = { SPIDER, 0, SPIDER, 100, SPIDER, 100, SPIDER, 100};
	const int enemies20[] = { SPIDER, 0, SPIDER, 50, SPIDER, 50, SPIDER, 50, SPIDER, 50, SPIDER, 50, SPIDER, 50, SPIDER, 50, SPIDER, 50, SPIDER, 50 };
	const int enemies21[] = { SPIDER, 0, SPIDER, 20, SPIDER, 20, SPIDER, 20, SPIDER, 20, TOUGHBEETLE, 150, TOUGHBEETLE, 150, TOUGHBEETLE, 150, TOUGHBEETLE, 150, TOUGHBEETLE, 150 };
	waves->push_back(std::make_shared<Wave>(enemies19, 8));
	waves->push_back(std::make_shared<Wave>(enemies20, 20));
	waves->push_back(std::make_shared<Wave>(enemies21, 20));
	pool3.push_back(std::make_shared<Fight>(waves));

	//day 10 fights
	std::vector<std::shared_ptr<Fight>> pool4;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies22[] = { RAT, 0, RAT, 50, RAT, 50, RAT, 50, RAT, 50 };
	const int enemies23[] = { RAT, 0, RAT, 50, RAT, 50, RAT, 50, RAT, 50, RAT, 50, RAT, 50, RAT, 50, RAT, 50, RAT, 50 };
	const int enemies24[] = { RAT, 0, RAT, 50, RAT, 50, GIANTRAT, 50 };
	const int enemies25[] = { RAT, 0, RAT, 50, RAT, 50, RAT, 50, RAT, 50, GIANTRAT, 50, RAT, 50, RAT, 50, GIANTRAT, 50, RAT, 50 };
	const int enemies26[] = { RAT, 0, RAT, 50, RAT, 50, RAT, 50, RAT, 50, RAT, 50, RAT, 50, GIANTRAT, 50, GIANTRAT, 50, GIANTRAT, 50 };
	const int enemies27[] = { GOBLIN, 0, GOBLIN, 50, GOBLIN, 50, GOBLIN, 50, GOBLIN, 50 };
	const int enemies28[] = { RAT, 0, RAT, 25, RAT, 25, RAT, 25, RAT, 25, GOBLIN, 50, GOBLIN, 50, GOBLIN, 50, GOBLIN, 50, GOBLIN, 50 };
	const int enemies29[] = { RAT, 0, RAT, 25, RAT, 25, RAT, 25, RAT, 25, GIANTRAT, 50, GIANTRAT, 50, GIANTRAT, 50, GOBLIN, 50, GOBLIN, 50, GOBLIN, 50, ORC, 100 };
	const int enemies30[] = { GOBLIN, 0, GOBLIN, 50, GOBLIN, 50, GOBLIN, 50, GOBLIN, 50, GOBLIN, 50, GOBLIN, 50, ORC, 50, ORC, 100, ORC, 100 };
	const int enemies31[] = { BOSSRAT, 0 };
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
	const int enemies32[] = { SLIME, 0, SLIME, 100, SLIME, 100, SLIME, 100, SLIME, 100 };
	const int enemies33[] = { SLIME, 0, SLIME, 60, SLIME, 60, SLIME, 60, SLIME, 60, SLIME, 60, SLIME, 60 };
	const int enemies34[] = { SLIME, 0, SLIME, 50, SLIME, 50, BLOB, 50 };
	const int enemies35[] = { SLIME, 0, SLIME, 50, SLIME, 50, SLIME, 50, SLIME, 50, BLOB, 150, BLOB, 150, BLOB, 150 };
	const int enemies36[] = { BLOB, 0, BLOB, 100, BLOB, 100, BLOB, 100, BLOB, 100 };
	const int enemies37[] = { BLOB, 0, BLOB, 100, BLOB, 100, OOZE, 150, OOZE, 100 };
	const int enemies38[] = { DOUBLEOOZE, 0 };
	const int enemies39[] = { SLIME, 0, SLIME, 50, SLIME, 50, SLIME, 50, BLOB, 100, BLOB, 100, BLOB, 100, OOZE, 150, OOZE, 150, OOZE, 150 };
	const int enemies40[] = { OOZE, 0, OOZE, 75, OOZE, 75, BLOB, 50, BLOB, 50, BLOB, 50, BLOB, 50, OOZE, 75, OOZE, 75, OOZE, 75 };
	const int enemies41[] = { DOUBLEOOZE, 0 , DOUBLEOOZE, 150};
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
	const int enemies42[] = { BEETLE, 0, BEETLE, 50, BEETLE, 50, BEETLE, 50, BEETLE, 50, BEETLE, 50, BEETLE, 50 };
	const int enemies43[] = { BEETLE, 0, BEETLE, 50, BEETLE, 50, BEETLE, 50, BEETLE, 50, BEETLE, 50, SPIDER, 150, SPIDER, 150, SPIDER, 150 };
	const int enemies44[] = { BEETLE, 0, BEETLE, 150, BEETLE, 150, BEETLE, 150, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10 };
	const int enemies45[] = { SPIDER, 0, SPIDER, 100, SPIDER, 100, SPIDER, 100, SPIDER, 100, SPIDER, 100 };
	const int enemies46[] = { SPIDER, 0, SPIDER, 100, SPIDER, 100, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, SPIDER, 100, SPIDER, 100, SPIDER, 100, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, SPIDER, 100, SPIDER, 100, SPIDER, 100 };
	const int enemies47[] = { SPIDER, 0, SPIDER, 100, SPIDER, 100, TOUGHBEETLE, 100, TOUGHBEETLE, 100 };
	const int enemies48[] = { TOUGHBEETLE, 0, TOUGHBEETLE, 50, TOUGHBEETLE, 50, TOUGHBEETLE, 50, TOUGHBEETLE, 50, TOUGHBEETLE, 50, TOUGHBEETLE, 50 };
	const int enemies49[] = { TOUGHBEETLE, 0, TOUGHBEETLE, 100, TOUGHBEETLE, 100, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, TOUGHBEETLE, 100, TOUGHBEETLE, 100, TOUGHBEETLE, 100, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, TOUGHBEETLE, 100, TOUGHBEETLE, 100, TOUGHBEETLE, 100 };
	const int enemies50[] = { TOUGHBEETLE, 0, TOUGHBEETLE, 100, SPIDER, 20, SPIDER, 20, SPIDER, 20, TOUGHBEETLE, 100, TOUGHBEETLE, 100, SPIDER, 20, SPIDER, 20, SPIDER, 20, TOUGHBEETLE, 100, TOUGHBEETLE, 100 };
	const int enemies51[] = { TANKBEETLE, 0 };
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
	const int enemies52[] = { RAT, 0, RAT, 30, RAT, 30, RAT, 30, RAT, 30, GIANTRAT, 100, GIANTRAT, 100, SHIELDRAT, 100 };
	const int enemies53[] = { SHIELDRAT, 0, SHIELDRAT, 50, SHIELDRAT, 50, SHIELDRAT, 50, SHIELDRAT, 50 };
	const int enemies54[] = { SHIELDRAT, 0, SHIELDRAT, 30, SHAMANRAT, 30, SHIELDRAT, 30, SHIELDRAT, 30 };
	waves->push_back(std::make_shared<Wave>(enemies52, 16));
	waves->push_back(std::make_shared<Wave>(enemies53, 10));
	waves->push_back(std::make_shared<Wave>(enemies54, 10));
	pool5.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies55[] = { JUMPINGOOZE, 0, JUMPINGOOZE, 150, JUMPINGOOZE, 200, JUMPINGOOZE, 200, BLOB, 200 };
	const int enemies56[] = { JUMPINGOOZE, 0, JUMPINGOOZE, 50, JUMPINGOOZE, 50, JUMPINGOOZE, 50, JUMPINGOOZE, 50 };
	const int enemies57[] = { JUMPINGOOZE, 0, JUMPINGOOZE, 50, JUMPINGOOZE, 50, OOZE, 150, OOZE, 150 };
	waves->push_back(std::make_shared<Wave>(enemies55, 10));
	waves->push_back(std::make_shared<Wave>(enemies56, 10));
	waves->push_back(std::make_shared<Wave>(enemies57, 10));
	pool5.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies58[] = { BLINKBUG, 0, BLINKBUG, 200, BLINKBUG, 200};
	const int enemies59[] = { TOUGHBEETLE, 0, BLINKBUG, 100, BLINKBUG, 50, TOUGHBEETLE, 100, TOUGHBEETLE, 100 };
	const int enemies60[] = { BLINKBUG, 0, BLINKBUG, 50, BLINKBUG, 50, BLINKBUG, 50, BLINKBUG, 50, BLINKBUG, 50, BLINKBUG, 50 };
	waves->push_back(std::make_shared<Wave>(enemies58, 6));
	waves->push_back(std::make_shared<Wave>(enemies59, 10));
	waves->push_back(std::make_shared<Wave>(enemies60, 14));
	pool5.push_back(std::make_shared<Fight>(waves));

	//Days 14-16
	std::vector<std::shared_ptr<Fight>> pool6;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies61[] = { GIANTRAT, 0, GIANTRAT, 100, GIANTRAT, 100, SHAMANRAT, 100, SHAMANRAT, 100, GIANTRAT, 100, GIANTRAT, 100, GIANTRAT, 100};
	const int enemies62[] = { SHIELDRAT, 0, SHIELDRAT, 100, SHAMANRAT, 100, SHAMANRAT, 50, SHAMANRAT, 50, SHIELDRAT, 100, SHIELDRAT, 100 };
	const int enemies63[] = { SHIELDRAT, 0, SHIELDRAT, 50, HEALERRAT, 50, HEALERRAT, 50, SHIELDRAT, 50, SHIELDRAT, 50, SHAMANRAT, 50, SHAMANRAT, 50, SHIELDRAT, 50, SHIELDRAT, 50 };
	waves->push_back(std::make_shared<Wave>(enemies61, 16));
	waves->push_back(std::make_shared<Wave>(enemies62, 14));
	waves->push_back(std::make_shared<Wave>(enemies63, 20));
	pool6.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies64[] = { OOZE, 0, OOZE, 150, OOZE, 200, BLOB, 200, BLOB, 200 };
	const int enemies65[] = { OOZE, 0, OOZE, 100, OOZE, 100, OOZE, 100, OOZE, 100, DOUBLER, 100, DOUBLER, 100 };
	const int enemies66[] = { BLOB, 0, BLOB, 50, BLOB, 50, DOUBLER, 150, DOUBLER, 150 };
	waves->push_back(std::make_shared<Wave>(enemies64, 10));
	waves->push_back(std::make_shared<Wave>(enemies65, 14));
	waves->push_back(std::make_shared<Wave>(enemies66, 10));
	pool6.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies67[] = { BLINKBUG, 0, BLINKBUG, 200, BLINKBUG, 200, RUNNERBEETLE, 200};
	const int enemies68[] = { TOUGHBEETLE, 0, BLINKBUG, 100, BLINKBUG, 50, RUNNERBEETLE, 100, RUNNERBEETLE, 100 };
	const int enemies69[] = { TOUGHBEETLE, 0, TOUGHBEETLE, 50, BLINKBUG, 50, BLINKBUG, 50, RUNNERBEETLE, 50, RUNNERBEETLE, 50, RUNNERBEETLE, 50 };
	waves->push_back(std::make_shared<Wave>(enemies67, 8));
	waves->push_back(std::make_shared<Wave>(enemies68, 10));
	waves->push_back(std::make_shared<Wave>(enemies69, 14));
	pool6.push_back(std::make_shared<Fight>(waves));

	//Days 17-19
	std::vector<std::shared_ptr<Fight>> pool7;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies70[] = { GIANTRAT, 0, GIANTRAT, 100, GIANTRAT, 100, SHAMANRAT, 100, SHAMANRAT, 100, GIANTRAT, 100, GIANTRAT, 100, GIANTRAT, 100 };
	const int enemies71[] = { SHIELDRAT, 0, SHIELDRAT, 100, SHAMANRAT, 100, SHAMANRAT, 50, SHAMANRAT, 50, SHIELDRAT, 100, SHIELDRAT, 100 };
	const int enemies72[] = { SHIELDRAT, 0, SHIELDRAT, 50, HEALERRAT, 50, HEALERRAT, 50, SHIELDRAT, 50, SHIELDRAT, 50, SHAMANRAT, 50, SHAMANRAT, 50, SHIELDRAT, 50, SHIELDRAT, 50 };
	waves->push_back(std::make_shared<Wave>(enemies70, 16));
	waves->push_back(std::make_shared<Wave>(enemies71, 14));
	waves->push_back(std::make_shared<Wave>(enemies72, 20));
	pool7.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies73[] = { OOZE, 0, OOZE, 150, OOZE, 200, BLOB, 200, BLOB, 200 };
	const int enemies74[] = { OOZE, 0, OOZE, 50, OOZE, 50, OOZE, 50, OOZE, 50, OOZE, 50, OOZE, 50, OOZE, 50, OOZE, 50, OOZE, 50 };
	const int enemies75[] = { OOZE, 0, OOZE, 50, OOZE, 50, DOUBLEOOZE, 150, DOUBLEOOZE, 150 };
	waves->push_back(std::make_shared<Wave>(enemies73, 10));
	waves->push_back(std::make_shared<Wave>(enemies74, 20));
	waves->push_back(std::make_shared<Wave>(enemies75, 10));
	pool7.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies76[] = { BLINKBUG, 0, BLINKBUG, 200, BLINKBUG, 200, RUNNERBEETLE, 200 };
	const int enemies77[] = { TOUGHBEETLE, 0, BLINKBUG, 100, BLINKBUG, 50, RUNNERBEETLE, 100, RUNNERBEETLE, 100 };
	const int enemies78[] = { TOUGHBEETLE, 0, TOUGHBEETLE, 50, BLINKBUG, 50, BLINKBUG, 50, RUNNERBEETLE, 50, RUNNERBEETLE, 50, RUNNERBEETLE, 50 };
	waves->push_back(std::make_shared<Wave>(enemies76, 8));
	waves->push_back(std::make_shared<Wave>(enemies77, 10));
	waves->push_back(std::make_shared<Wave>(enemies78, 14));
	pool7.push_back(std::make_shared<Fight>(waves));

	//Day 20
	std::vector<std::shared_ptr<Fight>> pool8;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies79[] = { RAT, 0, RAT, 30, RAT, 30, RAT, 30, GIANTRAT, 150, GIANTRAT, 150, GIANTRAT, 150, GIANTRAT, 150 };
	const int enemies80[] = { GIANTRAT, 0, GIANTRAT, 100, GIANTRAT, 100, GIANTRAT, 100, GIANTRAT, 100, SHIELDRAT, 150, SHIELDRAT, 150, SHIELDRAT, 150 };
	const int enemies81[] = { RAT, 0, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20, RAT, 20 };
	const int enemies82[] = { GIANTRAT, 0, GIANTRAT, 50, GIANTRAT, 50, GIANTRAT, 50, GIANTRAT, 50, GIANTRAT, 50, GIANTRAT, 50, GIANTRAT, 50 };
	const int enemies83[] = { SHIELDRAT, 0, SHIELDRAT, 100, SHIELDRAT, 100, SHIELDRAT, 100, SHAMANRAT, 100, SHAMANRAT, 100, SHAMANRAT, 100 };
	const int enemies84[] = { SHIELDRAT, 0, SHIELDRAT, 100, HEALERRAT, 100, HEALERRAT, 100, SHIELDRAT, 100, SHIELDRAT, 100, SHAMANRAT, 100, SHAMANRAT, 100, SHIELDRAT, 100, SHIELDRAT, 100 };
	const int enemies85[] = { BOSSRAT, 0, BOSSRAT, 300 };
	const int enemies86[] = { SHIELDRAT, 0, SHIELDRAT, 100, SHIELDRAT, 100, BOSSRAT, 100, HEALERRAT, 50, HEALERRAT, 50, SHAMANRAT, 50, SHAMANRAT, 50 };
	const int enemies87[] = { BOSSRAT, 0, BOSSRAT, 100, SHAMANRAT, 50, SHAMANRAT, 50, SHAMANRAT, 50, HEALERRAT, 50, HEALERRAT, 50, HEALERRAT, 50 };
	const int enemies88[] = { BOSSRAT, 0, BOSSRAT, 100, BOSSRAT, 100, BOSSRAT, 100, BOSSRAT, 100 };
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

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies89[] = { SLIME, 0, SLIME, 30, SLIME, 30, SLIME, 30, SLIME, 30, SLIME, 30, SLIME, 30, SLIME, 30, SLIME, 30, SLIME, 30, BLOB, 240, BLOB, 60, BLOB, 60 };
	const int enemies90[] = { BLOB, 0, BLOB, 50, BLOB, 50, DOUBLER, 150, DOUBLER, 150 }; 
	const int enemies91[] = { OOZE, 0, OOZE, 50, OOZE, 50, OOZE, 50, OOZE, 50, OOZE, 50, OOZE, 50, OOZE, 50, DOUBLER, 50, DOUBLER, 50 };
	const int enemies92[] = { JUMPINGOOZE, 0, JUMPINGOOZE, 50, JUMPINGOOZE, 50, JUMPINGOOZE, 50, OOZE, 50, OOZE, 50, OOZE, 50, OOZE, 50 };
	const int enemies93[] = { OOZE, 0, OOZE, 100, OOZE, 100, OOZE, 100, OOZE, 100, DOUBLEOOZE, 100, DOUBLEOOZE, 100 };
	const int enemies94[] = { OOZE, 0, OOZE, 100, OOZE, 100, BLOB, 100, BLOB, 100, BLOB, 100, OOZE, 100, OOZE, 100, OOZE, 100, OOZE, 100 };
	const int enemies95[] = { DOUBLEOOZE, 0, DOUBLEOOZE, 150, DOUBLEOOZE, 150, DOUBLEOOZE, 150 };
	const int enemies96[] = { OOZE, 0, OOZE, 100, OOZE, 100, DOUBLEOOZE, 100, OOZE, 50, OOZE, 50, OOZE, 50, DOUBLEOOZE, 50 };
	const int enemies97[] = { DOUBLEOOZE, 0, DOUBLEOOZE, 100, DOUBLEOOZE, 50, DOUBLER, 50, DOUBLER, 50, DOUBLEOOZE, 50, DOUBLEOOZE, 50, DOUBLEOOZE, 50 };
	const int enemies98[] = { MEGAOOZE, 0, MEGAOOZE, 60, MEGAOOZE, 60};
	waves->push_back(std::make_shared<Wave>(enemies89, 26));
	waves->push_back(std::make_shared<Wave>(enemies90, 10));
	waves->push_back(std::make_shared<Wave>(enemies91, 20));
	waves->push_back(std::make_shared<Wave>(enemies92, 16));
	waves->push_back(std::make_shared<Wave>(enemies93, 14));
	waves->push_back(std::make_shared<Wave>(enemies94, 20));
	waves->push_back(std::make_shared<Wave>(enemies95, 8));
	waves->push_back(std::make_shared<Wave>(enemies96, 16));
	waves->push_back(std::make_shared<Wave>(enemies97, 16));
	waves->push_back(std::make_shared<Wave>(enemies98, 6));
	pool8.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies99[] = { BLINKBUG, 0, BLINKBUG, 200, BLINKBUG, 200 };
	const int enemies100[] = { TOUGHBEETLE, 0, BLINKBUG, 100, BLINKBUG, 50, TOUGHBEETLE, 100, TOUGHBEETLE, 100 };
	const int enemies101[] = { BLINKBUG, 0, BLINKBUG, 50, BLINKBUG, 50, BLINKBUG, 50, BLINKBUG, 50, BLINKBUG, 50, BLINKBUG, 50 };
	const int enemies102[] = { BLINKBUG, 0, BLINKBUG, 200, BLINKBUG, 200, RUNNERBEETLE, 200 };
	const int enemies103[] = { TOUGHBEETLE, 0, BLINKBUG, 100, BLINKBUG, 50, RUNNERBEETLE, 100, RUNNERBEETLE, 100 };
	const int enemies104[] = { TOUGHBEETLE, 0, TOUGHBEETLE, 50, BLINKBUG, 50, BLINKBUG, 50, RUNNERBEETLE, 50, RUNNERBEETLE, 50, RUNNERBEETLE, 50 };
	const int enemies105[] = { BLINKBUG, 0, BLINKBUG, 200, BLINKBUG, 200, RUNNERBEETLE, 200 };
	const int enemies106[] = { TOUGHBEETLE, 0, BLINKBUG, 100, BLINKBUG, 50, RUNNERBEETLE, 100, RUNNERBEETLE, 100 };
	const int enemies107[] = { TOUGHBEETLE, 0, TOUGHBEETLE, 50, BLINKBUG, 50, BLINKBUG, 50, RUNNERBEETLE, 50, RUNNERBEETLE, 50, RUNNERBEETLE, 50 };
	const int enemies108[] = { WRITHINGMASS, 0 };
	waves->push_back(std::make_shared<Wave>(enemies99, 6));
	waves->push_back(std::make_shared<Wave>(enemies100, 10));
	waves->push_back(std::make_shared<Wave>(enemies101, 14));
	waves->push_back(std::make_shared<Wave>(enemies102, 8));
	waves->push_back(std::make_shared<Wave>(enemies103, 10));
	waves->push_back(std::make_shared<Wave>(enemies104, 14));
	waves->push_back(std::make_shared<Wave>(enemies105, 8));
	waves->push_back(std::make_shared<Wave>(enemies106, 10));
	waves->push_back(std::make_shared<Wave>(enemies107, 14));
	waves->push_back(std::make_shared<Wave>(enemies108, 2));
	pool8.push_back(std::make_shared<Fight>(waves));

	//Day 21-23
	std::vector<std::shared_ptr<Fight>> pool9;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies109[] = { PLAGUERAT, 0, PLAGUERAT, 50, PLAGUERAT, 50, PLAGUERAT, 50 };
	const int enemies110[] = { PLAGUERAT, 0, GIANTRAT, 50, GIANTRAT, 30, GIANTRAT, 30, PLAGUERAT, 50, GIANTRAT, 50, GIANTRAT, 30, GIANTRAT, 30, PLAGUERAT, 50, PLAGUERAT, 50 };
	const int enemies111[] = { ASSASSINRAT, 0, ASSASSINRAT, 50, ASSASSINRAT, 50, ASSASSINRAT, 50, BOSSRAT, 100, BOSSRAT, 50 };
	waves->push_back(std::make_shared<Wave>(enemies109, 8));
	waves->push_back(std::make_shared<Wave>(enemies110, 18));
	waves->push_back(std::make_shared<Wave>(enemies111, 12));
	pool9.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies112[] = { TOXICSLIME, 0, TOXICSLIME, 60,  TOXICSLIME, 60, TOXICSLIME, 60, TOXICSLIME, 60};
	const int enemies113[] = { DOUBLEOOZE, 0, DOUBLEOOZE, 60, DOUBLEOOZE, 60, DOUBLEOOZE, 60, DOUBLEOOZE, 60};
	const int enemies114[] = { MEGAOOZE, 0, MEGAOOZE, 60, MEGAOOZE, 60 };
	waves->push_back(std::make_shared<Wave>(enemies112, 10));
	waves->push_back(std::make_shared<Wave>(enemies113, 10));
	waves->push_back(std::make_shared<Wave>(enemies114, 6));
	pool9.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies115[] = { FIREFLY, 0, FIREFLY, 30, FIREFLY, 30, FIREFLY, 30, FIREFLY, 30 , FIREFLY, 30, FIREFLY, 30, FIREFLY, 30};
	const int enemies116[] = { GNAT, 0, GNAT, 60, GNAT, 60, GNAT, 60, GNAT, 60 };
	const int enemies117[] = { GNAT, 0, GNAT, 20, GNAT, 20, TANKBEETLE, 60, GNAT, 60, GNAT, 20, GNAT, 20, TANKBEETLE, 60, GNAT, 60, GNAT, 20, GNAT, 20 };
	waves->push_back(std::make_shared<Wave>(enemies115, 16));
	waves->push_back(std::make_shared<Wave>(enemies116, 10));
	waves->push_back(std::make_shared<Wave>(enemies117, 22));
	pool9.push_back(std::make_shared<Fight>(waves));

	//Day 24-26
	std::vector<std::shared_ptr<Fight>> pool10;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies118[] = { PLAGUERAT, 0, PLAGUERAT, 100, PLAGUERAT, 100, PLAGUERAT, 100, PLAGUERAT, 100 };
	const int enemies119[] = { PLAGUERAT, 0, PLAGUERAT, 30, PLAGUERAT, 30, PLAGUERAT, 30, WITCHRAT, 60, WITCHRAT, 30 };
	const int enemies120[] = { PLAGUERAT, 0, ASSASSINRAT, 100, PLAGUERAT, 100, ASSASSINRAT, 100, PLAGUERAT, 100, ASSASSINRAT, 100, PLAGUERAT, 100 };
	const int enemies121[] = { WITCHRAT, 0, WITCHRAT, 60, SHIELDRAT, 120, SHIELDRAT, 30, SHIELDRAT, 30, WITCHRAT, 60, WITCHRAT, 60, WITCHRAT, 60 };
	const int enemies122[] = { ASSASSINRAT, 0, ASSASSINRAT, 50, ASSASSINRAT, 50, BOSSRAT, 100, BOSSRAT, 100, ASSASSINRAT, 0, ASSASSINRAT, 50, ASSASSINRAT, 50 };
	waves->push_back(std::make_shared<Wave>(enemies118, 10));
	waves->push_back(std::make_shared<Wave>(enemies119, 12));
	waves->push_back(std::make_shared<Wave>(enemies120, 14));
	waves->push_back(std::make_shared<Wave>(enemies121, 16));
	waves->push_back(std::make_shared<Wave>(enemies122, 16));
	pool10.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies123[] = { TOXICSLIME, 0, TOXICSLIME, 60, TOXICSLIME, 60, TOXICSLIME, 60, TOXICSLIME, 60 };
	const int enemies124[] = { TOXICSLIME, 0, TOXICSLIME, 30, TOXICSLIME, 30, OOZE, 60, OOZE, 30, OOZE, 30, DOUBLEOOZE, 60, DOUBLEOOZE, 60 };
	const int enemies125[] = { TOXICSLIME, 0, DOUBLEOOZE, 60, TOXICSLIME, 60, DOUBLEOOZE, 60, TOXICSLIME, 60, DOUBLEOOZE, 60 };
	const int enemies126[] = { DOUBLEOOZE, 0, DOUBLEOOZE, 30,  JUMPINGOOZE, 60, JUMPINGOOZE, 20, JUMPINGOOZE, 20, JUMPINGOOZE, 20, JUMPINGOOZE, 20, MEGAOOZE, 60, MEGAOOZE, 60};
	const int enemies127[] = { SLIME, 0, SLIME, 20, SLIME, 20, BLOB, 60, BLOB, 20, BLOB, 20, OOZE, 60, OOZE, 20, OOZE, 20, DOUBLEOOZE, 60, DOUBLEOOZE, 20, DOUBLEOOZE, 20, MEGAOOZE, 60, MEGAOOZE, 60, MEGAOOZE, 60 };
	waves->push_back(std::make_shared<Wave>(enemies123, 10));
	waves->push_back(std::make_shared<Wave>(enemies124, 16));
	waves->push_back(std::make_shared<Wave>(enemies125, 12));
	waves->push_back(std::make_shared<Wave>(enemies126, 18));
	waves->push_back(std::make_shared<Wave>(enemies127, 30));
	pool10.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies128[] = { FIREFLY, 0, FIREFLY, 60, FIREFLY, 60, FIREFLY, 60, FIREFLY, 60, FIREFLY, 60 };
	const int enemies129[] = { GNAT, 0, GNAT, 100, GNAT, 100, GNAT, 100, GNAT, 100 };
	const int enemies130[] = { TANKBEETLE, 0, TANKBEETLE, 30, TANKBEETLE, 30, GNAT, 60, GNAT, 20, GNAT, 20, GNAT, 20, GNAT, 20 };
	const int enemies131[] = { BEETLE, 0, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10, BEETLE, 10,
		BLINKBUG, 60, BLINKBUG, 10, BLINKBUG, 10, BLINKBUG, 10, BLINKBUG, 10, BLINKBUG, 10, BLINKBUG, 10, BLINKBUG, 10, BLINKBUG, 10, BLINKBUG, 10, 
		GNAT, 60, GNAT, 20, GNAT,  GNAT, 20, GNAT, 20, GNAT, 20, GNAT, 20, GNAT, 20, GNAT, 20, GNAT, 20 };
	const int enemies132[] = { ANKHEG, 0, ANKHEG, 30, ANKHEG, 30, GNAT, 30, GNAT, 30, GNAT, 30, ANKHEG, 30, ANKHEG, 30, ANKHEG, 30 };
	waves->push_back(std::make_shared<Wave>(enemies128, 12));
	waves->push_back(std::make_shared<Wave>(enemies129, 10));
	waves->push_back(std::make_shared<Wave>(enemies130, 16));
	waves->push_back(std::make_shared<Wave>(enemies131, 60));
	waves->push_back(std::make_shared<Wave>(enemies132, 18));
	pool10.push_back(std::make_shared<Fight>(waves));

	//Day 27-29
	std::vector<std::shared_ptr<Fight>> pool11;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies133[] = { PLAGUERAT, 0, PLAGUERAT, 60, PLAGUERAT, 60, GIANTRAT, 60, GIANTRAT, 60 };
	const int enemies134[] = { GIANTRAT, 0, GIANTRAT, 60, GIANTRAT, 60, WITCHRAT, 60, WITCHRAT, 60 };
	const int enemies135[] = { ASSASSINRAT, 0, ASSASSINRAT, 60, ASSASSINRAT, 60, ASSASSINRAT, 60, ASSASSINRAT, 60 };
	const int enemies136[] = { GIANTRAT, 0, GIANTRAT, 30, GIANTRAT, 30, GIANTRAT, 30, SHAMANRAT, 30, SHAMANRAT, 30, SHAMANRAT, 30, ASSASSINRAT, 60, ASSASSINRAT, 30, ASSASSINRAT, 30  };
	const int enemies137[] = { BOSSRAT, 0,  BOSSRAT, 30, BOSSRAT, 30, HEALERRAT, 20, HEALERRAT, 20, SHAMANRAT, 20, SHAMANRAT, 20, ASSASSINRAT, 120, ASSASSINRAT, 30, ASSASSINRAT, 30, ASSASSINRAT, 30, ASSASSINRAT, 30 };
	waves->push_back(std::make_shared<Wave>(enemies133, 10));
	waves->push_back(std::make_shared<Wave>(enemies134, 10));
	waves->push_back(std::make_shared<Wave>(enemies135, 10));
	waves->push_back(std::make_shared<Wave>(enemies136, 20));
	waves->push_back(std::make_shared<Wave>(enemies137, 24));
	pool11.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies138[] = { SLIME, 0, SLIME, 20, SLIME, 20, SLIME, 20, SLIME, 20, SLIME, 20, SLIME, 20, SLIME, 20, SLIME, 20, SLIME, 20,
	SLIME, 20, SLIME, 20 , SLIME, 20 , SLIME, 20 , SLIME, 20 , SLIME, 20 , SLIME, 20 , SLIME, 20 , SLIME, 20 , SLIME, 20 ,
	SLIME, 20, SLIME, 20 , SLIME, 20 , SLIME, 20 , SLIME, 20 , SLIME, 20 , SLIME, 20 , SLIME, 20 , SLIME, 20 };
	const int enemies139[] = { BLOB, 0, BLOB, 40, BLOB, 40, BLOB, 40, BLOB, 40, BLOB, 40, BLOB, 40, BLOB, 40, BLOB, 40, BLOB, 40,
	BLOB, 40, BLOB, 40, BLOB, 40, BLOB, 40, BLOB, 40 };
	const int enemies140[] = { OOZE, 0, OOZE, 60, OOZE, 60, OOZE, 60, OOZE, 60, OOZE, 60, OOZE, 60, OOZE, 60, OOZE, 60, OOZE, 60 };
	const int enemies141[] = { DOUBLEOOZE,  0, DOUBLEOOZE, 80, DOUBLEOOZE, 80, DOUBLEOOZE, 80, DOUBLEOOZE, 80};
	const int enemies142[] = { MEGAOOZE, 0, MEGAOOZE, 100, MEGAOOZE, 100, MEGAOOZE, 100 };
	waves->push_back(std::make_shared<Wave>(enemies138, 60));
	waves->push_back(std::make_shared<Wave>(enemies139, 30));
	waves->push_back(std::make_shared<Wave>(enemies140, 20));
	waves->push_back(std::make_shared<Wave>(enemies141, 10));
	waves->push_back(std::make_shared<Wave>(enemies142, 8));
	pool11.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies143[] = { BEETLE, 0, FIREFLY, 20, BLINKBUG, 20, GNAT, 20, RUNNERBEETLE, 20, SPIDER, 20, 
		BEETLE, 0, FIREFLY, 20, BLINKBUG, 20, GNAT, 20, RUNNERBEETLE, 20, SPIDER, 20,
		BEETLE, 0, FIREFLY, 20, BLINKBUG, 20, GNAT, 20, RUNNERBEETLE, 20, SPIDER, 20 };
	const int enemies144[] = { FIREFLY, 0, BLINKBUG, 20, GNAT, 20, RUNNERBEETLE, 20, SPIDER, TANKBEETLE, 20,
		FIREFLY, 0, BLINKBUG, 20, GNAT, 20, RUNNERBEETLE, 20, SPIDER, TANKBEETLE, 20,
		FIREFLY, 0, BLINKBUG, 20, GNAT, 20, RUNNERBEETLE, 20, SPIDER, TANKBEETLE, 20 };
	const int enemies145[] = { BLINKBUG, 0, GNAT, 20, RUNNERBEETLE, 20, SPIDER, TANKBEETLE, 20, ANKHEG, 20,
		BLINKBUG, 0, GNAT, 20, RUNNERBEETLE, 20, SPIDER, TANKBEETLE, 20, ANKHEG, 20,
		BLINKBUG, 0, GNAT, 20, RUNNERBEETLE, 20, SPIDER, TANKBEETLE, 20, ANKHEG, 20 };
	const int enemies146[] = { BLINKBUG, 0, GNAT, 30, BLINKBUG, 30, GNAT, 30, BLINKBUG, 30, GNAT, 30, BLINKBUG, 30, GNAT, 30, BLINKBUG, 30, GNAT, 30 };
	const int enemies147[] = { ANKHEG, 0, ANKHEG, 30, ANKHEG, 30, ANKHEG, 30, ANKHEG, 30 };
	waves->push_back(std::make_shared<Wave>(enemies143, 36));
	waves->push_back(std::make_shared<Wave>(enemies144, 36));
	waves->push_back(std::make_shared<Wave>(enemies145, 36));
	waves->push_back(std::make_shared<Wave>(enemies146, 20));
	waves->push_back(std::make_shared<Wave>(enemies147, 10));
	pool11.push_back(std::make_shared<Fight>(waves));

	//Day 30
	std::vector<std::shared_ptr<Fight>> pool12;
	//Rats
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies148[] = { RAT };
	const int enemies149[] = { RAT };
	const int enemies150[] = { RAT };
	const int enemies151[] = { RAT };
	const int enemies152[] = { RAT };
	const int enemies153[] = { RAT };
	const int enemies154[] = { RAT };
	const int enemies155[] = { RAT };
	const int enemies156[] = { RAT };
	const int enemies157[] = { RAT };
	waves->push_back(std::make_shared<Wave>(enemies148, 1));
	waves->push_back(std::make_shared<Wave>(enemies149, 1));
	waves->push_back(std::make_shared<Wave>(enemies150, 1));
	waves->push_back(std::make_shared<Wave>(enemies151, 1));
	waves->push_back(std::make_shared<Wave>(enemies152, 1));
	waves->push_back(std::make_shared<Wave>(enemies153, 1));
	waves->push_back(std::make_shared<Wave>(enemies154, 1));
	waves->push_back(std::make_shared<Wave>(enemies155, 1));
	waves->push_back(std::make_shared<Wave>(enemies156, 1));
	waves->push_back(std::make_shared<Wave>(enemies157, 1));
	pool12.push_back(std::make_shared<Fight>(waves));

	//Oozes
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies158[] = { SLIME };
	const int enemies159[] = { SLIME };
	const int enemies160[] = { SLIME };
	const int enemies161[] = { SLIME };
	const int enemies162[] = { SLIME };
	const int enemies163[] = { SLIME };
	const int enemies164[] = { SLIME };
	const int enemies165[] = { SLIME };
	const int enemies166[] = { SLIME };
	const int enemies167[] = { SLIME };
	waves->push_back(std::make_shared<Wave>(enemies158, 1));
	waves->push_back(std::make_shared<Wave>(enemies159, 1));
	waves->push_back(std::make_shared<Wave>(enemies160, 1));
	waves->push_back(std::make_shared<Wave>(enemies161, 1));
	waves->push_back(std::make_shared<Wave>(enemies162, 1));
	waves->push_back(std::make_shared<Wave>(enemies163, 1));
	waves->push_back(std::make_shared<Wave>(enemies164, 1));
	waves->push_back(std::make_shared<Wave>(enemies165, 1));
	waves->push_back(std::make_shared<Wave>(enemies166, 1));
	waves->push_back(std::make_shared<Wave>(enemies167, 1));
	pool12.push_back(std::make_shared<Fight>(waves));

	//Bugs
	waves = std::make_shared<std::vector<std::shared_ptr<Wave>>>();
	const int enemies168[] = { BEETLE };
	const int enemies169[] = { BEETLE };
	const int enemies170[] = { BEETLE };
	const int enemies171[] = { BEETLE };
	const int enemies172[] = { BEETLE };
	const int enemies173[] = { BEETLE };
	const int enemies174[] = { BEETLE };
	const int enemies175[] = { BEETLE };
	const int enemies176[] = { BEETLE };
	const int enemies177[] = { BEETLE };
	waves->push_back(std::make_shared<Wave>(enemies168, 1));
	waves->push_back(std::make_shared<Wave>(enemies169, 1));
	waves->push_back(std::make_shared<Wave>(enemies170, 1));
	waves->push_back(std::make_shared<Wave>(enemies171, 1));
	waves->push_back(std::make_shared<Wave>(enemies172, 1));
	waves->push_back(std::make_shared<Wave>(enemies173, 1));
	waves->push_back(std::make_shared<Wave>(enemies174, 1));
	waves->push_back(std::make_shared<Wave>(enemies175, 1));
	waves->push_back(std::make_shared<Wave>(enemies176, 1));
	waves->push_back(std::make_shared<Wave>(enemies177, 1));
	pool12.push_back(std::make_shared<Fight>(waves));

	//determine combats from random pool
	s_Fights->push_back(pool1[fightOrder[0]]);
	s_Fights->push_back(pool1[fightOrder[1]]);
	s_Fights->push_back(pool1[fightOrder[2]]);
	s_Fights->push_back(pool2[fightOrder[3]]);
	s_Fights->push_back(pool2[fightOrder[4]]);
	s_Fights->push_back(pool2[fightOrder[5]]);
	s_Fights->push_back(pool3[fightOrder[6]]);
	s_Fights->push_back(pool3[fightOrder[7]]);
	s_Fights->push_back(pool3[fightOrder[8]]);
	s_Fights->push_back(pool4[fightOrder[9]]);
	s_Fights->push_back(pool5[fightOrder[10]]);
	s_Fights->push_back(pool5[fightOrder[11]]);
	s_Fights->push_back(pool5[fightOrder[12]]);
	s_Fights->push_back(pool6[fightOrder[13]]);
	s_Fights->push_back(pool6[fightOrder[14]]);
	s_Fights->push_back(pool6[fightOrder[15]]);
	s_Fights->push_back(pool7[fightOrder[16]]);
	s_Fights->push_back(pool7[fightOrder[17]]);
	s_Fights->push_back(pool7[fightOrder[18]]);
	s_Fights->push_back(pool8[fightOrder[19]]);
	s_Fights->push_back(pool9[fightOrder[20]]);
	s_Fights->push_back(pool9[fightOrder[21]]);
	s_Fights->push_back(pool9[fightOrder[22]]);
	s_Fights->push_back(pool10[fightOrder[23]]);
	s_Fights->push_back(pool10[fightOrder[24]]);
	s_Fights->push_back(pool10[fightOrder[25]]);
	s_Fights->push_back(pool11[fightOrder[26]]);
	s_Fights->push_back(pool11[fightOrder[27]]);
	s_Fights->push_back(pool11[fightOrder[28]]);
	s_Fights->push_back(pool12[fightOrder[29]]);
}