#pragma once
#include "Tile.h"

namespace TowerDefense
{
	class Board
	{
	public:
		Board(const Board&) = delete;
		static Board& Get();

		void Update();

		void Render();

		//Path should be alternating x and y coordinates of tiles from start to end
		//0, 0 is the bottom left corner of the board
		void SetPath(const int path[], int size);

		//Returns true if the currently held tower can fit in the selected space
		bool ValidPlace();

		//Returns true if the x and y location is on the board
		bool Contains(float x, float y) const;

		void SetSelectedTileSize(int width, int height);

		inline int GetWidth() const { return m_Width; }

		inline std::shared_ptr<Tile> GetCurrentTile() const { return m_CurrentTile; }

		inline std::shared_ptr<StaticImage> GetSelectedTile() const { return m_SelectedTile; }

		inline std::shared_ptr<std::vector<std::shared_ptr<Tile>>> GetTiles() const { return m_Tiles; }

		inline std::shared_ptr<std::vector<int>> GetPath() const { return m_Path; }

		//Called at end of program to clean up memory
		//Necessary to unbind static and singleton GLFW textures before calling glfwTerminate
		void CleanUp();

	private:
		Board(int width, int height);

		void SetTileImage(int x, int y, int tileImage);

		std::unique_ptr<float[]> GetPositions(unsigned int tileNumber, int xOff, int yOff);

		std::pair<float, float> GetCoords(unsigned int tileNumber);

		float m_X, m_Y;
		int m_Width, m_Height;
		bool m_TileSelected;

		//The tile that the mouse is currently over
		std::shared_ptr<Tile> m_CurrentTile;
		
		//The selected area of the currently held tower
		std::shared_ptr<StaticImage> m_SelectedTile;

		std::shared_ptr<std::vector<std::shared_ptr<Tile>>> m_Tiles;

		std::shared_ptr<std::vector<int>> m_Path;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<float[]> m_Positions;

		Vec3 m_Position;
	};
}