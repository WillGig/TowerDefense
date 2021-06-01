#pragma once
#include "cards/Card.h"

namespace TowerDefense
{
	namespace Enemy { class Enemy; }

	namespace Tower { class Tower; enum class DamageType; }

	class Artifact : public Entity
	{
	public:
		Artifact(const std::string name)
			:Entity(0.0f, 0.0f, 64, 64, 0.0f, name, Type::ARTIFACT), m_Name(name),
			m_DetailedImage(std::make_unique<Image>(name, 400.0f, 350.0f, 128, 128, 0.0f)),
			m_NameText(std::make_unique<Text>(name, 400.0f, 280.0f, 14.0f, 0.0f)),
			m_InfoImage(std::make_unique<Image>(name + "Info", 400.0f, 200.0f, 220, 85, 0.0f))
		{
			m_NameText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		inline void Update() override {}
		inline void RenderArtifactDetails() { m_DetailedImage->Render(); m_InfoImage->Render(); m_NameText->Render(); }
		inline virtual void OnAquire() {}
		inline virtual void OnAddCard(std::shared_ptr<Card> c) {}
		inline virtual void OnRoundStart() {}
		inline virtual void OnCardPlay(std::shared_ptr<Card> c) {}
		inline virtual void OnFightStart() {}
		inline virtual void OnFightEnd() {}
		inline virtual void OnAddHouse() {}
		inline virtual void OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type) {}
		inline virtual void OnEnemyReachedEnd(std::shared_ptr<Enemy::Enemy> e) {}

		inline const std::string& GetName() const { return m_Name; }

		static std::shared_ptr<Artifact> GetRandomArtifact();
		static void CleanUp();

	private:
		std::string m_Name;
		std::unique_ptr<Text> m_NameText;
		std::unique_ptr<Image> m_DetailedImage, m_InfoImage;

		static std::unique_ptr<std::vector<std::shared_ptr<Artifact>>> s_Artifacts;
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

	class TokenOfTheBroken : public Artifact
	{
	public:
		TokenOfTheBroken();
		void OnFightStart() override;
	};

	class TokenOfTheVigilant : public Artifact
	{
	public:
		TokenOfTheVigilant();
		void OnCardPlay(std::shared_ptr<Card> c) override;
	private:
		int m_Counter;
	};

	class BlessingOfTheBat : public Artifact
	{
	public:
		BlessingOfTheBat();
		void OnCardPlay(std::shared_ptr<Card> c) override;
	};

	class LuckyAxe : public Artifact
	{
	public:
		LuckyAxe();	
		void OnAquire() override;
	};

	class LuckyPickaxe : public Artifact
	{
	public:
		LuckyPickaxe();
		void OnAquire() override;
	};

	class LuckySythe : public Artifact
	{
	public:
		LuckySythe();
		void OnAquire() override;
	};

	class Boulder : public Artifact
	{
	public:
		Boulder();
		void OnAquire() override;
	};

	class MagicBeans : public Artifact
	{
	public:
		MagicBeans();
		void OnAquire() override;
	};

	class FruitCake : public Artifact
	{
	public:
		FruitCake();
		void OnAquire() override;
	};

	class DollHouse : public Artifact
	{
	public:
		DollHouse();
		void OnAquire() override;
	};

	class ToyDolls : public Artifact
	{
	public:
		ToyDolls();
		void OnAquire() override;
		void OnAddHouse() override;
	private:
		int m_NumberAdded;
	};

	class HandOfMidas : public Artifact
	{
	public:
		HandOfMidas();
		void OnAquire() override;
	};

	class HouseExpansionKit : public Artifact
	{
	public:
		HouseExpansionKit();
		void OnAquire() override;
		void OnAddHouse() override;
	};

	class Thermos : public Artifact
	{
	public:
		Thermos();
		void OnFightStart() override;
	};

	class Cooler : public Artifact
	{
	public:
		Cooler();
		void OnFightStart() override;
		void OnFightEnd() override;
	private:
		int m_EndEnergy;
	};

	class MiniatureWormHole : public Artifact
	{
	public:
		MiniatureWormHole();
		void OnFightStart() override;
		void OnEnemyReachedEnd(std::shared_ptr<Enemy::Enemy> e) override;

	private:
		bool m_Ready;
	};

	class SpecialToxins : public Artifact
	{
	public:
		SpecialToxins();
		void OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type) override;
	};
}