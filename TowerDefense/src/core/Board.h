#pragma once
#include "Tile.h"

#define EMPTY		0xffffff
#define PATH		0xffff00
#define STARTTILE   0x00ff00
#define ENDTILE     0xff0000
#define ROCK		0xA5A5A5
#define TREE		0x007F0E

namespace TowerDefense
{
	class Board
	{
	public:
		Board(const Board&) = delete;
		static Board& Get();

		void Update();

		void Render();

		void LoadMapNumber(int num);

		void LoadMap(const std::string& file);

		//Selects a random map file from res/maps and loads it
		void LoadRandomMap();

		//Only to be used for design in the map editor
		//NOT to be called during combat
		void Clear();
		void SetTile(int x, int y, int tile);
		void Save(int mapNumber);

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

		inline float GetX() const { return m_X; }
		inline float GetY() const { return m_Y; }

		static int TILESIZE;

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
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Texture> m_Texture;
		std::unique_ptr<float[]> m_Positions;

		Vec3 m_Position;
	};
}