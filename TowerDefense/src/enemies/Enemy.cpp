#include "pch.h"
#include "Enemy.h"
#include "core/Board.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "scenes/Combat.h"
#include "core/Clock.h"
#include "towers/Tower.h"

int TowerDefense::Enemy::Enemy::POISONTICKRATE = 30;

TowerDefense::Enemy::Enemy::Enemy(int width, int height, float health, float speed, const std::string& name)
	:Entity(0.0f, 0.0f, width, height, 0.0f, name, Type::ENEMY), m_Damage(1), m_CurrentTile(0),
	m_SlowTime(0), m_PoisonTime(0), m_PoisonTick(0), m_StunTime(0), m_Health(health), m_MaxHealth(health), m_Speed(speed), 
	m_SlowPercent(0.0f), m_PoisonAmount(0.0f), m_GoalX(), m_GoalY(), m_DistanceTraveled(0.0f), m_ReachedEnd(false), 
	m_Selected(false), m_Clicked(false), m_Name(name),
	m_RegularImage(std::make_shared<Image>(name, 0.0f, 0.0f, width, height, 0.0f)), 
	m_SelectedImage(std::make_shared<Image>(name + "Selected", 0.0f, 0.0f, width, height, 0.0f)),
	m_HealthBar(std::make_unique<HealthBar>(m_X, m_Y + height/2, 20.0f, 4.0f))
{
	TowerDefense::Board& board = TowerDefense::Board::Get();
	int tileX = board.GetPath()->at(0);
	int tileY = board.GetPath()->at(1);
	SetX(board.GetTiles()->at(tileX + tileY * board.GetWidth())->GetX());
	SetY(board.GetTiles()->at(tileX + tileY * board.GetWidth())->GetY());
	FindNewGoal();
}

void TowerDefense::Enemy::Enemy::Update()
{
	CheckClicked();

	UpdateImage();

	if (Combat::Paused())
		return;

	if(m_StunTime == 0)
		Move();

	UpdateDebuffs();

	//Check if enemy reached the end and Remove
	if (m_ReachedEnd) {
		TowerDefense::Player::Get().ChangeHealth(-m_Damage);
		Combat::GetCurrentFight()->AddEscapedEnemy(*this);
		Destroy();
	}

}

void TowerDefense::Enemy::Enemy::Render()
{
	Entity::Render();
	m_HealthBar->Render();
}

//Set Image to selected or unselected
void TowerDefense::Enemy::Enemy::UpdateImage()
{
	if (m_Selected)
	{
		SetImage(m_SelectedImage);
		m_Selected = false;
	}
	else
	{
		SetImage(m_RegularImage);
	}
}

void TowerDefense::Enemy::Enemy::Move()
{
	//Check if within 1 step of goal
	bool reachedX = abs(m_GoalX - m_X) < m_Speed * (1.0f - m_SlowPercent) * Combat::GetRoundSpeed();
	bool reachedY = abs(m_GoalY - m_Y) < m_Speed * (1.0f - m_SlowPercent) * Combat::GetRoundSpeed();

	if (reachedX && reachedY)
	{
		//Calculate extra movement towards new goal
		float extraMovement = m_Speed * (1.0f - m_SlowPercent) * Combat::GetRoundSpeed() - abs(m_X - m_GoalX) - abs(m_Y - m_GoalY);
		SetX(m_GoalX);
		SetY(m_GoalY);
		FindNewGoal();
		SetX(m_X + extraMovement * (float)sin(m_Rotation * PI / 180.0f));
		SetY(m_Y - extraMovement * (float)cos(m_Rotation * PI / 180.0f));
	}
	else
	{
		//Move normally towards goal
		SetX(m_X + m_Speed * (1.0f - m_SlowPercent) * Combat::GetRoundSpeed() * (float)sin(m_Rotation * PI / 180.0f));
		SetY(m_Y - m_Speed * (1.0f - m_SlowPercent) * Combat::GetRoundSpeed() * (float)cos(m_Rotation * PI / 180.0f));
		m_DistanceTraveled += m_Speed * (1.0f - m_SlowPercent) * Combat::GetRoundSpeed();
	}
}

void TowerDefense::Enemy::Enemy::UpdateDebuffs()
{
	//Update Slows
	if (m_SlowTime > 0) {
		m_SlowTime -= Combat::GetRoundSpeed();
		if (m_SlowTime < 1) {
			m_SlowPercent = 0.0;
			m_SlowTime = 0;
		}
	}

	//update Poison
	if (m_PoisonTime > 0) {
		m_PoisonTime -= Combat::GetRoundSpeed();
		if (m_PoisonTick >= POISONTICKRATE) {
			TakeDamage(m_PoisonAmount * Combat::GetRoundSpeed(), m_PoisonSource);
			m_PoisonTick = 0;
		}
		else
			m_PoisonTick += Combat::GetRoundSpeed();

		if (m_PoisonTime < 1) {
			m_PoisonAmount = 0.0;
			m_PoisonTime = 0;
			m_HealthBar->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
			m_PoisonSource = 0;
			m_PoisonTick = 0;
		}
	}

	//Update Stun
	if (m_StunTime > 0)
	{
		m_StunTime -= Combat::GetRoundSpeed();
		if (m_StunTime < 1) {
			m_StunTime = 0;
		}
	}
}


void TowerDefense::Enemy::Enemy::Destroy()
{
	Combat::RemoveEntity(m_ID);
}

void TowerDefense::Enemy::Enemy::FindNewGoal()
{
	TowerDefense::Board& board = TowerDefense::Board::Get();

	auto tiles = board.GetTiles();
	auto path = board.GetPath();

	if (m_CurrentTile > (int)path->size() - 1) {
		m_ReachedEnd = true;
		return;
	}

	m_GoalX = tiles->at(path->at(m_CurrentTile) + path->at(m_CurrentTile + 1) * board.GetWidth())->GetX();
	m_GoalY = tiles->at(path->at(m_CurrentTile) + path->at(m_CurrentTile + 1) * board.GetWidth())->GetY();

	if (m_GoalX > m_X) {
		SetRotation(90.0f);
	}
	else if (m_GoalX < m_X) {
		SetRotation(270.0f);
	}
	else if (m_GoalY < m_Y) {
		SetRotation(0.0f);
	}
	else if (m_GoalY > m_Y) {
		SetRotation(180.0f);
	}

	m_CurrentTile += 2;
}

void TowerDefense::Enemy::Enemy::TakeDamage(float damage, unsigned int sourceID)
{
	auto source = Combat::GetEntity(sourceID);
	if (source)
	{
		if (source->GetEntityType() == Type::TOWER)
		{
			auto tower = std::dynamic_pointer_cast<Tower::Tower>(source);
			tower->AddDamageDelt(damage);
		}
		Combat::OnEnemyHit(GetID(), source);
		Combat::GetCurrentFight()->AddDamage(damage, source);
	}
		
	m_Health -= damage;
	m_HealthBar->SetFill(m_Health / m_MaxHealth);
	if (m_Health <= 0)
	{
		Combat::GetCurrentFight()->AddDefeatedEnemy(*this);
		Combat::OnEnemyDeath(GetID());
		Destroy();
	}
}

void TowerDefense::Enemy::Enemy::Slow(float slowPercent, int slowTime)
{
	if (m_SlowPercent < slowPercent)
		m_SlowPercent = slowPercent;
	if (m_SlowTime < slowTime)
		m_SlowTime = slowTime;
}

void TowerDefense::Enemy::Enemy::Poison(float poisonDamage, int poisonTime, unsigned int source)
{
	if (m_PoisonTime < poisonTime)
		m_PoisonTime = poisonTime;
	if (m_PoisonAmount < poisonDamage)
		m_PoisonAmount = poisonDamage;
	m_HealthBar->SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_PoisonSource = source;
}

void TowerDefense::Enemy::Enemy::CheckClicked()
{
	m_Clicked = false;
	bool cardSelected = Player::Get().GetHand()->GetSelectedCard() != -1;

	if (Contains(Input::GetMouseX(), Input::GetMouseY()) && !cardSelected && !Combat::DraggingInfo() && Input::GetLeftMouseClickedAndSetFalse())
		m_Clicked = true;
}