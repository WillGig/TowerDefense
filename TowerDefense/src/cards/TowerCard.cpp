#include "pch.h"
#include "TowerCard.h"
#include "core/Board.h"
#include "scenes/Combat.h"
#include "core/Player.h"

TowerDefense::TowerCard::TowerCard(const std::string& name, int cost, const std::string& image, const std::string& upgradedImage)
	:Card(name, CardType::TOWER, cost, image, upgradedImage)
{
}

void TowerDefense::TowerCard::Render()
{
	if (m_OverBoard)
	{
		m_HeldTower->Render();
		m_HeldTower->GetRangeCircle()->Render();
	}
	else
		Entity::Render();
}

void TowerDefense::TowerCard::Update()
{

	//Update Held tower position if over board and create held tower if null
	TowerDefense::Board& board = TowerDefense::Board::Get();
	if (board.Contains(m_X, m_Y))
	{
		m_OverBoard = true;
		if (m_HeldTower)
		{
			m_HeldTower->SetX(board.GetSelectedTile()->GetX());
			m_HeldTower->SetY(board.GetSelectedTile()->GetY());

			if (board.ValidPlace())
				m_HeldTower->GetRangeCircle()->SetColor(0.0f, 1.0f, 0.0f, 1.0f);
			else
				m_HeldTower->GetRangeCircle()->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			m_HeldTower = GetTower();
			m_HeldTower->SetX(board.GetSelectedTile()->GetX());
			m_HeldTower->SetY(board.GetSelectedTile()->GetY());
			board.SetSelectedTileSize(m_HeldTower->GetWidth(), m_HeldTower->GetHeight());
		}
	}
	else
		m_OverBoard = false;

	//Highlight towers in range if holding a support tower
	if (m_OverBoard && m_HeldTower->GetType() == Tower::TowerType::SUPPORT) {
		auto entities = Combat::GetEntities();
		for (unsigned int i = 0; i < entities->size(); i++) {
			std::shared_ptr<TowerDefense::Entity> e = entities->at(i);
			if (e->GetEntityType() == Type::TOWER) {
				if (m_HeldTower->GetDistance(e->GetX(), e->GetY()) < m_HeldTower->GetRange())
					std::dynamic_pointer_cast<Tower::Tower>(e)->SetHighlighted();
			}
		}
	}

}

bool TowerDefense::TowerCard::Play()
{
	Board& board = Board::Get();

	if (m_OverBoard && board.ValidPlace()) {
		//Add tower to board
		m_HeldTower->SetX(board.GetSelectedTile()->GetX());
		m_HeldTower->SetY(board.GetSelectedTile()->GetY());
		Combat::AddEntity(m_HeldTower);

		//Set occupied tiles
		std::shared_ptr<StaticImage> s = board.GetSelectedTile();
		auto tiles = board.GetTiles();
		for (unsigned int i = 0; i < tiles->size(); i++) {
			std::shared_ptr<Tile> t = tiles->at(i);
			if (s->Contains(t->GetX(), t->GetY())) {
				t->SetContainedObject(m_HeldTower);
			}
		}
		m_OverBoard = false;
		m_HeldTower.reset();
		return true;
	}
	m_OverBoard = false;
	return false;
}

void TowerDefense::TowerCard::Upgrade()
{
	Card::Upgrade();
	AddInfoCard(std::make_shared<InfoTile>("UpgradedInfo"));
}