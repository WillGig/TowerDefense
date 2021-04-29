#pragma once
#include "core/Entity.h"
#include "cards/Card.h"

namespace TowerDefense
{
	class Artifact : public Entity
	{
	public:
		Artifact(const std::string name)
			:Entity(0.0f, 0.0f, 32, 32, 0.0f, name, Type::ARTIFACT), m_Name(name),
			m_DetailedImage(std::make_unique<Image>(name, 400.0f, 300.0f, 128, 128, 0.0f))
		{
		}
		inline void Update() override {};
		inline void RenderArtifactDetails() { m_DetailedImage->Render(); };
		inline virtual void OnAquire() {};
		inline virtual void OnAddCard(std::shared_ptr<Card> c) {};
		inline virtual void OnRoundStart() {};
		inline virtual void OnCardPlay(std::shared_ptr<Card> c) {};
		inline virtual void OnFightStart() {};
		inline virtual void OnFightEnd() {};

	private:
		std::string m_Name;
		std::unique_ptr<Image> m_DetailedImage;
	};

	class TokenOfTheMute : public Artifact
	{
	public:
		TokenOfTheMute();
		void OnFightStart() override;
	};

	class TokenOfTheArmored : public Artifact
	{
	public:
		TokenOfTheArmored();
		void OnFightEnd() override;
	};
}