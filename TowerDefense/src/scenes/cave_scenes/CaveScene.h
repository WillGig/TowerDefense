#pragma once
#include "scenes/Scene.h"

namespace TowerDefense
{
	class CaveScene : public Scene
	{
	public:
		inline void OnSwitch() override {};
		inline bool Exit() { return m_Exit; }

		static std::shared_ptr<CaveScene> GetRandomCaveEvent();

	protected:
		bool m_Exit = false;
	};

	//Restore to full hp or +10 max hp
	class FountainOfYouth : public CaveScene
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

	//Sets your deck on fire (add 3 flame cards) OR sets you on fire (-20 hp)
	class LiterallySatan : public CaveScene
	{
	public:
		LiterallySatan();
		void Render() override;
		void Update() override;
	};

	//Fight (-1 hp), Feed (-10hp, get bat's blessing)
	class CaveBat : public CaveScene
	{
	public:
		CaveBat();
		void Render() override;
		void Update() override;
	};

	//Bus of puppies is going to run over a child. Divert to crash into 10 convicts instead, killing them and the children
	//Third choice "But this has nothing to do with the game!" (-1 hp)
	class TrolleyProblem : public CaveScene
	{
	public:
		TrolleyProblem();
		void Render() override;
		void Update() override;
	};

	//Do something here
	class KnightsWhoSayNah : public CaveScene
	{
	public:
		KnightsWhoSayNah();
		void Render() override;
		void Update() override;
	};
}
