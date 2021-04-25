#pragma once

namespace TowerDefense
{
	enum class Type {STATICIMAGE, ANIMATION, BUTTON, CARD, CARDPILE, ENEMY, TOWER, PROJECTILE};

	class Entity
	{
	public:
		Entity(float x, float y, int width, int height, float rotation, const std::string& image, Type type);

		virtual void Render();

		virtual void Update() = 0;

		virtual void EndRound();

		bool Contains(float x, float y) const;

		float GetDistance(float x, float y) const;

		inline int GetID() const { return m_ID; }
		inline Type GetEntityType() const { return m_EntityType; }

		inline int GetWidth() const { return m_Width; }
		inline void SetWidth(int w) { m_Width = w; SetImage(std::make_shared<Image>(m_Image->GetFile(), m_X, m_Y, m_Width, m_Height, m_Rotation)); }

		inline int GetHeight() const { return m_Height; }
		inline void SetHeight(int h) { m_Height = h; SetImage(std::make_shared<Image>(m_Image->GetFile(), m_X, m_Y, m_Width, m_Height, m_Rotation)); }

		inline float GetX() const { return m_X; }
		inline virtual void SetX(float x) { m_X = x; m_Image->SetPosition(m_X, m_Y, 0.0f); }

		inline float GetY() const { return m_Y; }
		inline virtual void SetY(float y) { m_Y = y; m_Image->SetPosition(m_X, m_Y, 0.0f); }

		inline float GetRotation() const { return m_Rotation; }
		inline virtual void SetRotation(float rotation) { m_Rotation = rotation; m_Image->SetRotation(m_Rotation); }

		void SetImage(std::shared_ptr<Image> image);

	protected:
		//Unique ID assigned to each entity at creation
		unsigned int m_ID;

		Type m_EntityType;
		
		int m_Width, m_Height;
		
		float m_X, m_Y, m_Rotation;
		
		std::shared_ptr<Image> m_Image;

	private:
		//Counter to assign IDs starts at 0 and increments every time an entity is created
		static unsigned int s_ID;
	};
}