#pragma once
#include "Scene.h"
#include "core/Tile.h"

namespace TowerDefense
{
	class MapEditor : public Scene
	{
	public:
		MapEditor();
		void Update() override;
		void Render() override;
		void OnSwitch() override;
	private:
		void SetMap(int m);

		int m_NumMaps, m_CurrentMap, m_CurrentTile;
		std::string m_CurrentTileTexture;

		std::array<std::unique_ptr<TowerDefense::Button>, 7> m_Buttons;
		std::array<std::unique_ptr<TowerDefense::Button>, 6> m_Tiles;

		std::unique_ptr<Text> m_CurrentMapName;
		std::unique_ptr<Rectangle> m_CurrentTileHighlight;
		std::unique_ptr<Image> m_PotentialTile;

		std::stack<std::vector<Tile>> m_UndoHistory;
		std::vector<Tile> m_CurrentChange;
	};
}
