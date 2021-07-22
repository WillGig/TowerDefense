#include "pch.h"
#include "Enemy.h"
#include "core/Board.h"
#include "TowerDefense.h"
#include "core/Player.h"
#include "scenes/Combat.h"
#include "core/Clock.h"
#include "towers/Tower.h"

int TowerDefense::Enemy::Enemy::POISONTICKRATE = 30;

TowerDefense::Enemy::Enemy::Enemy(int width, int height, float health, float speed, int goldValue, const std::string& name, int damage)
	:Entity(0.0f, 0.0f, width, height, 0.0f, name, Type::ENEMY), m_Damage(damage), m_CurrentTile(-2),
	m_SlowTime(0), m_PoisonTime(0), m_PoisonTick(0), m_StunTime(0), m_Health(health), m_Armor(0.0f), 
	m_MagicResistance(0.0f), m_MaxHealth(health), m_Speed(speed), m_GoldValue(goldValue), m_Bounty(0), 
	m_SlowPercent(0.0f), m_PoisonAmount(0.0f), m_StunResist(0.0f), m_GoalX(), m_GoalY(), m_DistanceTraveled(0.0f), 
	m_ReachedEnd(false), m_Selected(false), m_Clicked(false), m_Name(name),
	m_RegularImage(std::make_shared<Image>(name, 0.0f, 0.0f, width, height, 0.0f)), 
	m_SelectedImage(std::make_shared<Image>(name + "Selected", 0.0f, 0.0f, width, height, 0.0f)),
	m_HealthBar(std::make_unique<HealthBar>(m_X, m_Y + height/2, 20.0f, 4.0f)),
	m_DamageIcon(std::make_unique<Image>("DamageIcon", m_X + 5, m_Y + m_Height / 2 + 10, 16, 16, 0.0f)),
	m_DamageText(std::make_unique<Text>(std::to_string(m_Damage), m_X - 5, m_Y + m_Height / 2 + 10, 10.0f, 0.0f))
{
	m_DamageText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_DamageText->SetDropShadow(1.0f);
	Board& board = Board::Get();
	int tileX = board.GetPath()->at(0);
	int tileY = board.GetPath()->at(1);
	SetX(board.GetTiles()->at(tileX + tileY * board.GetWidth())->GetX());
	SetY(board.GetTiles()->at(tileX + tileY * board.GetWidth())->GetY());
	FindNewGoal(m_X, m_Y);
}

void TowerDefense::Enemy::Enemy::Update()
{
	CheckClicked();

	UpdateImage();

	if (Combat::Paused())
		return;

	if (m_StunTime == 0)
	{
		for(int i = 0; i < Combat::GetRoundSpeed(); i++)
			Move();
	}

	UpdateDebuffs();

	//Check if enemy reached the end and Remove
	if (m_ReachedEnd) {

		Player::Get().ArtifactOnEnemyReachedEnd(std::dynamic_pointer_cast<Enemy>(Combat::GetEntity(GetID())));

		if (m_ReachedEnd)
		{
			Combat::GetCurrentFight()->AddEscapedEnemy(*this);
			TowerDefense::Player::Get().ChangeHealth(-m_Damage);
			Destroy();
		}
	}

}

void TowerDefense::Enemy::Enemy::Render()
{
	Entity::Render();
	m_HealthBar->Render();
	m_DamageIcon->Render();
	m_DamageText->Render();
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
	bool reachedX = abs(m_GoalX - m_X) < m_Speed * (1.0f - m_SlowPercent);
	bool reachedY = abs(m_GoalY - m_Y) < m_Speed * (1.0f - m_SlowPercent);

	if (reachedX && reachedY)
	{
		//Calculate extra movement towards new goal
		float extraMovement = m_Speed * (1.0f - m_SlowPercent) - abs(m_X - m_GoalX) - abs(m_Y - m_GoalY);
		SetX(m_GoalX);
		SetY(m_GoalY);
		FindNewGoal(m_X, m_Y);
		SetX(m_X + extraMovement * (float)sin(m_Rotation * PI / 180.0f));
		SetY(m_Y - extraMovement * (float)cos(m_Rotation * PI / 180.0f));
	}
	else
	{
		//Move normally towards goal
		SetX(m_X + m_Speed * (1.0f - m_SlowPercent) * (float)sin(m_Rotation * PI / 180.0f));
		SetY(m_Y - m_Speed * (1.0f - m_SlowPercent) * (float)cos(m_Rotation * PI / 180.0f));
		m_DistanceTraveled += m_Speed * (1.0f - m_SlowPercent) ;
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
			TakeDamage(m_PoisonAmount * Combat::GetRoundSpeed(), m_PoisonSource, Tower::DamageType::POISON);
			m_PoisonTick = 0;
		}
		else
			m_PoisonTick += Combat::GetRoundSpeed();

		if (m_PoisonTime < 1) {
			m_PoisonAmount = 0.0;
			m_PoisonTime = 0;
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

void TowerDefense::Enemy::Enemy::FindNewGoal(float x, float y)
{
	m_CurrentTile += 2;
	Board& board = Board::Get();
	auto tiles = board.GetTiles();
	auto path = board.GetPath();

	if (m_CurrentTile > (int)path->size() - 1) {
		m_ReachedEnd = true;
		return;
	}

	m_GoalX = tiles->at(path->at(m_CurrentTile) + path->at(m_CurrentTile + 1) * board.GetWidth())->GetX();
	m_GoalY = tiles->at(path->at(m_CurrentTile) + path->at(m_CurrentTile + 1) * board.GetWidth())->GetY();

	if (m_GoalX > x) {
		SetRotation(90.0f);
	}
	else if (m_GoalX < x) {
		SetRotation(270.0f);
	}
	else if (m_GoalY < y) {
		SetRotation(0.0f);
	}
	else if (m_GoalY > y) {
		SetRotation(180.0f);
	}
}

void TowerDefense::Enemy::Enemy::TakeDamage(float damage, unsigned int sourceID, Tower::DamageType type)
{
	if (m_Health <= 0)
		return;

	float effectiveDamage = damage;

	if (type == Tower::DamageType::PHYSICAL)
		effectiveDamage *= (100.0f / (100.0f + m_Armor));
	else if (type == Tower::DamageType::MAGIC || type == Tower::DamageType::POISON)
		effectiveDamage *= (100.0f / (100.0f + m_MagicResistance));

	auto source = Combat::GetEntity(sourceID);
	if (source)
	{
		if (source->GetEntityType() == Type::TOWER)
		{
			auto tower = std::dynamic_pointer_cast<Tower::Tower>(source);
			tower->AddDamageDealt(effectiveDamage);
		}
		Combat::OnEnemyHit(GetID(), source, type);
		Player::Get().ArtifactOnEnemyHit(std::dynamic_pointer_cast<Enemy>(Combat::GetEntity(GetID())), source, type);
		Combat::GetCurrentFight()->AddDamage(effectiveDamage, source);
	}
		
	ChangeHealth(-effectiveDamage);
}

void TowerDefense::Enemy::Enemy::ChangeHealth(float change)
{
	m_Health += change;
	if (m_Health > m_MaxHealth)
		m_Health = m_MaxHealth;

	float totalPoisonDamage = m_PoisonAmount * (m_PoisonTime/POISONTICKRATE) * (100.0f / (100.0f + m_MagicResistance));
	m_HealthBar->SetFill(m_Health / m_MaxHealth, totalPoisonDamage/m_Health);
	m_HealthBar->SetPosition(m_X - (10.0f - m_HealthBar->GetBarWidth()/2), m_Y + m_Height / 2);
	if (m_Health <= 0)
	{
		Combat::GetCurrentFight()->AddDefeatedEnemy(*this);
		Combat::OnEnemyDeath(GetID());
		if(m_Bounty != 0)
			Player::Get().ChangeResource(m_Bounty, Resource::GOLD);
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
	float totalPoisonDamage = m_PoisonAmount * (m_PoisonTime / POISONTICKRATE) * (100.0f / (100.0f + m_MagicResistance));
	m_HealthBar->SetFill(m_Health / m_MaxHealth, totalPoisonDamage / m_Health);
	m_PoisonSource = source;
}

void TowerDefense::Enemy::Enemy::Stun(int stunTime)
{ 
	if (stunTime > m_StunTime)
	{
		m_StunTime = (int)(stunTime * (5.0f / (5.0f + m_StunResist)));
		m_StunResist += 1.0f;
	}
};

void TowerDefense::Enemy::Enemy::SetX(float x) 
{
	m_X = x; 
	m_Image->SetPosition(m_X, m_Y, 0.0f); 
	m_HealthBar->SetPosition(m_X - (10.0f - m_HealthBar->GetBarWidth() / 2), m_Y + m_Height / 2);
	m_DamageIcon->SetPosition(m_X + 5, m_Y + m_Height / 2 + 10, 0.0f);
	m_DamageText->SetPosition(m_X - 5, m_Y + m_Height / 2 + 10, 0.0f);
}
void TowerDefense::Enemy::Enemy::SetY(float y) 
{ 
	m_Y = y; 
	m_Image->SetPosition(m_X, m_Y, 0.0f); 
	m_HealthBar->SetPosition(m_X - (10.0f - m_HealthBar->GetBarWidth() / 2), m_Y + m_Height / 2);
	m_DamageIcon->SetPosition(m_X + 5, m_Y + m_Height / 2 + 10, 0.0f);
	m_DamageText->SetPosition(m_X - 5, m_Y + m_Height / 2 + 10, 0.0f);
}

void TowerDefense::Enemy::Enemy::SetDamage(int damage)
{
	m_Damage = damage;
	if (m_Damage < 0)
		m_Damage = 0;
	m_DamageText = std::make_unique<Text>(std::to_string(m_Damage), m_X - 5, m_Y + m_Height / 2 + 10, 10.0f, 0.0f);
	m_DamageText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_DamageText->SetDropShadow(1.0f);
}

void TowerDefense::Enemy::Enemy::CheckClicked()
{
	m_Clicked = false;
	bool cardSelected = Player::Get().GetHand()->GetSelectedCard() != -1;

	if (Contains(Input::GetMouseX(), Input::GetMouseY()) && !cardSelected && !Combat::DraggingInfo() && Input::GetLeftMouseClickedAndSetFalse())
		m_Clicked = true;
}

void TowerDefense::Enemy::Enemy::SetDistanceTravelled(float distanceTravelled)
{
	Board& board = Board::Get();
	m_DistanceTraveled = 0;
	m_CurrentTile = 0;
	m_ReachedEnd = false;
	
	int tileX = board.GetPath()->at(0);
	int tileY = board.GetPath()->at(1);
	SetX(board.GetTiles()->at(tileX + tileY * board.GetWidth())->GetX());
	SetY(board.GetTiles()->at(tileX + tileY * board.GetWidth())->GetY());
	FindNewGoal(m_X, m_Y);

	while (m_DistanceTraveled < distanceTravelled)
		Move();

}