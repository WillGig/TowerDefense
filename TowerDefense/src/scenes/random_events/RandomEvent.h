#pragma once
#include "scenes/Scene.h"
#include "scenes/CombatReward.h"

namespace TowerDefense
{
	class RandomEvent : public Scene
	{
	public:
		inline void OnSwitch() override {};
		inline bool Exit() { return m_Exit; }
		inline virtual const std::string GetName() = 0;

		static std::shared_ptr<RandomEvent> GetRandomEvent();

		static std::shared_ptr<std::vector<std::shared_ptr<RandomEvent>>> GetRemainingEvents();

		static void SetRemainingEvents(std::shared_ptr<std::vector<std::shared_ptr<RandomEvent>>> e);

		static void CleanUp();

	protected:
		bool m_Exit = false;

	private:
		static std::shared_ptr<std::vector<std::shared_ptr<RandomEvent>>> s_Events;
	};

	//Restore to full hp or +10 max hp
	class FountainOfYouth : public RandomEvent
	{
	public:
		FountainOfYouth();
		void Render() override;
		void Update() override;
		inline const std::string GetName() override { return "FountainOfYouth"; }
	private:
		std::unique_ptr<StaticImage> m_Image;
		std::unique_ptr<Button> m_Button1, m_Button2;
		std::unique_ptr<Text> m_Text1, m_Text2, m_Prompt;
	};

	//Sets your deck on fire (add 3 flame cards) OR sets YOU on fire (-30 hp)
	class LiterallySatan : public RandomEvent
	{
	public:
		LiterallySatan();
		void Render() override;
		void Update() override;
		inline const std::string GetName() override { return "Devil"; }
	private:
		std::unique_ptr<StaticImage> m_Image;
		std::unique_ptr<Button> m_Button1, m_Button2;
		std::unique_ptr<Text> m_Text1, m_Text2, m_Prompt;
	};

	//Fight (-1 hp), Feed (-10hp, get bat's blessing)
	class CaveBat : public RandomEvent
	{
	public:
		CaveBat();
		void Render() override;
		void Update() override;
		inline const std::string GetName() override { return "CaveBat"; }
	private:
		std::unique_ptr<StaticImage> m_Image;
		std::unique_ptr<Button> m_Button1, m_Button2;
		std::unique_ptr<Text> m_Text1, m_Text2, m_Prompt;
	};

	//Truck of puppies is going to run over a baby. Divert to crash into 3 convicts instead, killing them and the puppies
	//Third choice "But this has nothing to do with the game!" (-1 hp)
	class TrolleyProblem : public RandomEvent
	{
	public:
		TrolleyProblem();
		void Render() override;
		void Update() override;
		inline const std::string GetName() override { return "Trolley"; }
	private:
		std::unique_ptr<StaticImage> m_Image;
		std::unique_ptr<Button> m_Button1, m_Button2, m_Button3;
		std::unique_ptr<Text> m_Text1, m_Text2, m_Text3, m_Prompt;
	};

	class KnightsWhoSayNah : public RandomEvent
	{
	public:
		KnightsWhoSayNah();
		void Render() override;
		void Update() override;
		inline const std::string GetName() override { return "KnightsWhoSayNah"; }

	private:
		std::unique_ptr<Image> m_Image;
		std::unique_ptr<Button> m_Button1, m_Button2, m_Button3;
		std::unique_ptr<Text> m_Text1, m_Text2, m_Text3, m_Prompt;
	};

	class FrogPrince : public RandomEvent
	{
	public:
		FrogPrince();
		void Render() override;
		void Update() override;
		inline const std::string GetName() override { return "FrogPrince"; }

	private:
		std::unique_ptr<StaticImage> m_Image;
		std::unique_ptr<Button> m_Button1, m_Button2;
		std::unique_ptr<Text> m_Text1, m_Text2, m_Prompt;
	};

	class Treasure : public RandomEvent
	{
	public:
		Treasure();
		void Render() override;
		void Update() override;
		inline const std::string GetName() override { return "Treasure"; }

	private:
		std::unique_ptr<Image> m_Image;
		std::unique_ptr<Button> m_Continue;
		std::unique_ptr<Text> m_Prompt;

		std::unique_ptr<ResourceReward> m_Gold;
		std::unique_ptr<ArtifactReward> m_Artifact;
	};

	class WanderingSage : public RandomEvent
	{
	public:
		WanderingSage();
		void Render() override;
		void Update() override;
		inline const std::string GetName() override { return "WanderingSage"; }

	private:
		std::unique_ptr<StaticImage> m_Image;
		std::unique_ptr<Button> m_Button1, m_Button2;
		std::unique_ptr<Text> m_Text1, m_Text2, m_Prompt;
	};

	class WanderingBard : public RandomEvent
	{
	public:
		WanderingBard();
		void Render() override;
		void Update() override;
		inline const std::string GetName() override { return "WanderingBard"; }

	private:
		std::unique_ptr<StaticImage> m_Image;
		std::unique_ptr<Button> m_Button1, m_Button2;
		std::unique_ptr<Text> m_Text1, m_Text2, m_Prompt;
	};

	class WanderingCleric : public RandomEvent
	{
	public:
		WanderingCleric();
		void Render() override;
		void Update() override;
		inline const std::string GetName() override { return "WanderingCleric"; }

	private:
		std::unique_ptr<StaticImage> m_Image;
		std::unique_ptr<Button> m_Button1, m_Button2;
		std::unique_ptr<Text> m_Text1, m_Text2, m_Prompt;
	};

	class TheBlackKnight : public RandomEvent
	{
	public:
		TheBlackKnight();
		void Render() override;
		void Update() override;
		inline const std::string GetName() override { return "BlackKnight"; }

	private:
		std::unique_ptr<StaticImage> m_Image;
		std::unique_ptr<Button> m_Button1, m_Button2;
		std::unique_ptr<Text> m_Text1, m_Text2, m_Prompt;
	};
}
