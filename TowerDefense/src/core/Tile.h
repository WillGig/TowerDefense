#pragma once

namespace TowerDefense
{

	class Tile
	{
	public:
		Tile(float x, float y, int width, int height);
		inline bool IsOccupied() { return (m_ContainedObject != nullptr) || m_Occupied; }
		inline std::shared_ptr<Entity> GetContainedObject() const { return m_ContainedObject; }
		void SetContainedObject(std::shared_ptr<Entity> object);
		bool Contains(float x, float y) const;
		inline void SetOccupied(bool occupied) { m_Occupied = occupied; }
		inline float GetX() const { return m_X; }
		inline float GetY() const { return m_Y; }
		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
	private:
		float m_X, m_Y;
		int m_Width, m_Height;

		//May not be true even if there is a tower in the tile. Used for keeping track of non-objects such as path tiles
		//Always use IsOccupied() to check if a tile is available
		bool m_Occupied;

		//Any entity that takes up the tile such as a tower
		//Large towers may be contained in multiple tiles. Each tile should hold a reference to that tower.
		std::shared_ptr<Entity> m_ContainedObject;
	};
}