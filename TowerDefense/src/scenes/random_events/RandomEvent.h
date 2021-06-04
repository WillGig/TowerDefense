#pragma once
#include "scenes/Scene.h"

namespace TowerDefense
{
	class RandomEvent : public Scene
	{
	public:
		inline void OnSwitch() override {};
		inline bool Exit() { return m_Exit; }

		static std::shared_ptr<RandomEvent> GetRandomCaveEvent();

	protected:
		bool m_Exit = false;
	};

	//Restore to full hp or +10 max hp
	class FountainOfYouth : public RandomEvent
	{
	public:
		FountainOfYouth();
		void Render() override;
		void Update() override;
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
	private:
		std::unique_ptr<StaticImage> m_Image;
		std::unique_ptr<Button> m_Button1, m_Button2, m_Button3;
		std::unique_ptr<Text> m_Text1, m_Text2, m_Text3, m_Prompt;
	};

	//Do something here
	class KnightsWhoSayNah : public RandomEvent
	{
	public:
		KnightsWhoSayNah();
		void Render() override;
		void Update() override;
	};
}
