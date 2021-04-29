#pragma once
#include "core/Entity.h"
#include "cards/Card.h"

namespace TowerDefense
{
	class Artifact : public Entity
	{
	public:
		Artifact(const std::string name)
			:Entity(0.0f, 0.0f, 32, 32, 0.0f, name, Type::ARTIFACT), m_Name(name)
		{
		}
		inline void Update() override {};
		inline void RenderArtifactDetails() {}; //TODO render render artifact info tiles
		inline virtual void OnAquire() {};
		inline virtual void OnAddCard(std::shared_ptr<Card> c) {};
		inline virtual void OnRoundStart() {};
		inline virtual void OnCardPlay(std::shared_ptr<Card> c) {};
		inline virtual void OnFightStart() {};
		inline virtual void OnFightEnd() {};

	private:
		std::string m_Name;
	};

	class TokenOfTheMute : public Artifact
	{
	public:
		TokenOfTheMute();
		void OnFightStart() override;
	};
}