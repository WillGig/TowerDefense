#include "pch.h"
#include "MapEditor.h"
#include "TowerDefense.h"
#include "core/Board.h"

TowerDefense::MapEditor::MapEditor()
	:m_CurrentTileHighlight(std::make_unique<Rectangle>(0.0f, 0.0f, 30.0f, 30.0f))
{	
	m_Buttons =
	{
		std::make_unique<Button>(40.0f, 40.0f, 40, 40, "saveMap"),
		std::make_unique<Button>(90.0f, 40.0f, 40, 40, "deleteMap"),
		std::make_unique<Button>(140.0f, 40.0f, 40, 40, "previousMap"),
		std::make_unique<Button>(190.0f, 40.0f, 40, 40, "nextMap"),
		std::make_unique<Button>(240.0f, 40.0f, 40, 40, "newMap"),
		std::make_unique<Button>(290.0f, 40.0f, 40, 40, "undoChange"),
		std::make_unique<Button>(760.0f, 40.0f, 40, 40, "mapToMenu")
	};

	m_Tiles =
	{
		std::make_unique<Button>(80.0f,  200.0f, 25, 25, "emptyTile"),
		std::make_unique<Button>(110.0f, 200.0f, 25, 25, "pathTile"),
		std::make_unique<Button>(140.0f, 200.0f, 25, 25, "startTile"),
		std::make_unique<Button>(170.0f, 200.0f, 25, 25, "endTile"),
		std::make_unique<Button>(200.0f, 200.0f, 25, 25, "rockTile"),
		std::make_unique<Button>(230.0f, 200.0f, 25, 25, "treeTile")
	};
}

void TowerDefense::MapEditor::Render()
{
	Board::Get().Render();
	if (m_PotentialTile)
		m_PotentialTile->Render();

	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->Render();
	m_CurrentTileHighlight->Render();
	for (unsigned int i = 0; i < m_Tiles.size(); i++)
		m_Tiles[i]->Render();
	m_CurrentMapName->Render();
}

void TowerDefense::MapEditor::Update()
{
	Board& board = Board::Get();
	//Check if Tile on board is clicked
	board.Update();
	auto tile = board.GetCurrentTile();
	if (tile)
	{
		m_PotentialTile = std::make_unique<Image>(m_CurrentTileTexture, tile->GetX(), tile->GetY(), Board::TILESIZE, Board::TILESIZE, 0.0f);
		
		if (Input::GetLeftMouseClicked())
		{
			//Get Tile coords
			int x = (int)((tile->GetX() - board.GetX()) / Board::TILESIZE);
			int y = (int)((tile->GetY() - board.GetY() + 1) / Board::TILESIZE);

			//Check if tile has already been changed this click
			bool containsTile = false;
			for (Tile t : m_CurrentChange)
				if (t.GetX() == x && t.GetY() == y)
				{
					containsTile = true;
					break;
				}

			//Change tile and add to history
			if (!containsTile)
			{
				m_CurrentChange.push_back(Tile((float)x, (float)y, 0, 0, tile->GetTexture()));
				board.SetTile(x, y, m_CurrentTile);
			}
		}
	}
	else if(m_PotentialTile)
			m_PotentialTile.reset();

	//When mouse is released, add change to undo history
	if (!Input::GetLeftMouseClicked() && m_CurrentChange.size() > 0)
	{
		m_UndoHistory.push(m_CurrentChange);
		m_CurrentChange = std::vector<Tile>();
	}
		

	//Check if currentTile is changed
	for (unsigned int i = 0; i < m_Tiles.size(); i++)
		m_Tiles[i]->Update();
	if (m_Tiles[0]->IsClicked())
	{
		m_CurrentTile = EMPTY;
		m_CurrentTileTexture = "emptyTile";
		m_CurrentTileHighlight->SetPosition(m_Tiles[0]->GetX(), m_Tiles[0]->GetY(), 0.0f);
	}
	else if (m_Tiles[1]->IsClicked())
	{
		m_CurrentTile = PATH;
		m_CurrentTileTexture = "pathTile";
		m_CurrentTileHighlight->SetPosition(m_Tiles[1]->GetX(), m_Tiles[1]->GetY(), 0.0f);
	}
	else if (m_Tiles[2]->IsClicked())
	{
		m_CurrentTile = STARTTILE;
		m_CurrentTileTexture = "startTile";
		m_CurrentTileHighlight->SetPosition(m_Tiles[2]->GetX(), m_Tiles[2]->GetY(), 0.0f);
	}
	else if (m_Tiles[3]->IsClicked())
	{
		m_CurrentTile = ENDTILE;
		m_CurrentTileTexture = "endTile";
		m_CurrentTileHighlight->SetPosition(m_Tiles[3]->GetX(), m_Tiles[3]->GetY(), 0.0f);
	}
	else if (m_Tiles[4]->IsClicked())
	{
		m_CurrentTile = ROCK;
		m_CurrentTileTexture = "rockTile";
		m_CurrentTileHighlight->SetPosition(m_Tiles[4]->GetX(), m_Tiles[4]->GetY(), 0.0f);
	}
	else if (m_Tiles[5]->IsClicked())
	{
		m_CurrentTile = TREE;
		m_CurrentTileTexture = "treeTile";
		m_CurrentTileHighlight->SetPosition(m_Tiles[5]->GetX(), m_Tiles[5]->GetY(), 0.0f);
	}

	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->Update();

	//Save Current Map
	if (m_Buttons[0]->IsClicked())
	{
		board.Save(m_CurrentMap);
	}
	//Delete Current Map
	else if (m_Buttons[1]->IsClicked())
	{
		if (m_CurrentMap > 2)
		{
			//Delete the current map
			std::string file = "res/maps/map" + std::to_string(m_CurrentMap) + ".png";
			if (std::remove(file.c_str()) != 0)
				std::cout << "Error deleting map";

			//Lower names of later maps
			int m = m_CurrentMap;
			while (m < m_NumMaps - 1)
			{
				auto oldName = "res/maps/map" + std::to_string(m+1) + ".png";
				auto newName = "res/maps/map" + std::to_string(m) + ".png";
				if(rename(oldName.c_str(), newName.c_str()) != 0)
					std::cout << "Error adjusting map names";
				m++;
			}

			m_CurrentMap--;
			m_NumMaps--;
			SetMap(m_CurrentMap);
		}
	}
	//Load Previous Map
	else if (m_Buttons[2]->IsClicked())
	{
		if (m_CurrentMap > 0)
		{
			SetMap(m_CurrentMap - 1);
			m_CurrentMap--;
		}
	}
	//Load Next Map
	else if (m_Buttons[3]->IsClicked())
	{
		if (m_CurrentMap < m_NumMaps - 1)
		{
			SetMap(m_CurrentMap + 1);
			m_CurrentMap++;
		}
	}
	//Create a New Map
	else if (m_Buttons[4]->IsClicked())
	{
		m_CurrentMap = m_NumMaps;
		m_NumMaps++;

		board.Clear();
		board.Save(m_CurrentMap);
		m_CurrentMapName = std::make_unique<Text>("res/maps/map" + std::to_string(m_CurrentMap) + ".png", 400.0f, 575.0f, 14.0f, 0.0f);
	}
	//Undo Last Change
	else if (m_Buttons[5]->IsClicked() || ((Input::GetKeyPressed(GLFW_KEY_LEFT_CONTROL) || Input::GetKeyPressed(GLFW_KEY_RIGHT_CONTROL)) && Input::GetKeyPressedAndSetFalse(GLFW_KEY_Z)))
	{
		if (m_UndoHistory.size() > 0)
		{
			//Restore old tile data from undo history
			auto oldTiles = m_UndoHistory.top();
			for (Tile t : oldTiles)
				board.SetTile((int)t.GetX(), (int)t.GetY(), t.GetTexture());
			m_UndoHistory.pop();
		}
	}
	//Return to Main Menu
	else if (m_Buttons[6]->IsClicked())
	{
		SetScene(SceneType::MAINMENU);
	}
}

void TowerDefense::MapEditor::OnSwitch()
{
	m_CurrentMap = 0;
	m_NumMaps = 0;
	m_CurrentTile = 0;
	m_CurrentTileTexture = "emptyTile";
	m_CurrentTileHighlight->SetPosition(m_Tiles[0]->GetX(), m_Tiles[0]->GetY(), 0.0f);

	bool exists = true;
	while (exists)
	{
		std::ifstream file("res/maps/map" + std::to_string(m_NumMaps) + ".png");

		exists = (bool)file;

		if (exists)
		{
			m_NumMaps++;
			file.close();
		}
	}

	SetMap(0);
}

void TowerDefense::MapEditor::SetMap(int m)
{
	Board::Get().LoadMapNumber(m);
	m_CurrentMapName = std::make_unique<Text>("res/maps/map" + std::to_string(m) + ".png", 400.0f, 575.0f, 14.0f, 0.0f);
	m_CurrentMapName->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_CurrentChange = std::vector<Tile>();
	m_UndoHistory = std::stack<std::vector<Tile>>();
}