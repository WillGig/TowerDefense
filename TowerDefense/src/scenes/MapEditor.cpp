#include "pch.h"
#include "MapEditor.h"
#include "TowerDefense.h"
#include "core/Board.h"

TowerDefense::MapEditor::MapEditor()
{	
	m_Buttons =
	{
		std::make_unique<Button>(40.0f, 40.0f, 40, 40, "saveMap"),
		std::make_unique<Button>(100.0f, 40.0f, 40, 40, "deleteMap"),
		std::make_unique<Button>(160.0f, 40.0f, 40, 40, "previousMap"),
		std::make_unique<Button>(220.0f, 40.0f, 40, 40, "nextMap"),
		std::make_unique<Button>(280.0f, 40.0f, 40, 40, "newMap"),
		std::make_unique<Button>(340.0f, 40.0f, 40, 40, "undoChange"),
		std::make_unique<Button>(760.0f, 40.0f, 40, 40, "mapToMenu")
	};

	m_Tiles =
	{
		std::make_unique<Button>(80.0f, 150.0f, 25, 25, "emptyTile"),
		std::make_unique<Button>(110.0f, 150.0f, 25, 25, "pathTile"),
		std::make_unique<Button>(140.0f, 150.0f, 25, 25, "startTile"),
		std::make_unique<Button>(170.0f, 150.0f, 25, 25, "endTile"),
		std::make_unique<Button>(200.0f, 150.0f, 25, 25, "rockTile"),
		std::make_unique<Button>(230.0f, 150.0f, 25, 25, "treeTile")
	};
}

void TowerDefense::MapEditor::Render()
{
	Board::Get().Render();
	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->Render();
	for (unsigned int i = 0; i < m_Tiles.size(); i++)
		m_Tiles[i]->Render();
	m_CurrentMapName->Render();
}

void TowerDefense::MapEditor::Update()
{
	//Check if Tile on board is clicked
	Board::Get().Update();
	auto tile = Board::Get().GetCurrentTile();
	if (tile && Input::GetLeftMouseClicked())
	{
		int x = (int)((tile->GetX() - Board::Get().GetX()) / Board::TILESIZE);
		int y = (int)((tile->GetY() - Board::Get().GetY() + 1) / Board::TILESIZE);
		std::cout << y << std::endl;
		Board::Get().SetTile(x, y, m_CurrentTile);
	}
		

	//Check if currentTile is changed
	for (unsigned int i = 0; i < m_Tiles.size(); i++)
		m_Tiles[i]->Update();
	if (m_Tiles[0]->IsClicked())
	{
		m_CurrentTile = EMPTY;
	}
	else if (m_Tiles[1]->IsClicked())
	{
		m_CurrentTile = PATH;
	}
	else if (m_Tiles[2]->IsClicked())
	{
		m_CurrentTile = STARTTILE;
	}
	else if (m_Tiles[3]->IsClicked())
	{
		m_CurrentTile = ENDTILE;
	}
	else if (m_Tiles[4]->IsClicked())
	{
		m_CurrentTile = ROCK;
	}
	else if (m_Tiles[5]->IsClicked())
	{
		m_CurrentTile = TREE;
	}

	for (unsigned int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i]->Update();

	//Save Current Map
	if (m_Buttons[0]->IsClicked())
	{
		Board::Get().Save(m_CurrentMap);
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

		Board::Get().Clear();
		Board::Get().Save(m_CurrentMap);
		m_CurrentMapName = std::make_unique<Text>("res/maps/map" + std::to_string(m_CurrentMap) + ".png", 400.0f, 575.0f, 14.0f, 0.0f);
	}
	//Undo Last Change
	else if (m_Buttons[5]->IsClicked())
	{
		//TODO
	}
	//Return to Main Menu
	else if (m_Buttons[6]->IsClicked())
	{
		SetScene(SceneType::MAINMENU);
	}
}

void TowerDefense::MapEditor::OnSwitch()
{
	//Change Background Color
	Renderer::Get().Clear(237.0f / 255.0f, 225.0f / 255.0f, 190.0f / 255.0f, 1.0f);

	m_CurrentMap = 0;
	m_NumMaps = 0;

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
}