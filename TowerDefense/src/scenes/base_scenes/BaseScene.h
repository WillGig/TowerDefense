#pragma once
#include "scenes/Scene.h"
#include "scenes/random_events/RandomEvent.h"
#include "cards/CardChoice.h"
#include "BuildButton.h"
#include "CardSlot.h"
#include "ArtifactSlot.h"
#include "ClickCircle.h"

namespace TowerDefense
{
	class BuildButton;

	class Artifact;

	class BaseScene : public Scene
	{
	public:
		inline bool Exit() const { return m_Exit; }
		inline void RenderButton() { m_Button->Render(); }
		inline void UpdateButton() { m_Button->Update(); }
		inline bool ButtonClicked() const { return m_Button->IsClicked(); }
		inline bool ButtonSelected() const { return m_Button->IsSelected(); }
		inline void SetButtonPosition(float x, float y) { m_Button->SetX(x); m_Button->SetY(y); }
		inline void RenderText() { m_Description->Render(); }
		inline void OnSwitch() override { m_Exit = false; m_Button->SetSelected(false); };
		virtual std::string GetName() = 0;
		inline int GetActivityReady() const { return m_ActivityReady; }
		inline void SetActivityReady(int ready) { m_ActivityReady = ready; }

	protected:
		BaseScene(const std::string& button, const std::string& description, int coolDown)
			:m_Exit(false), m_ActivityCoolDown(coolDown), m_ActivityReady(0), 
			m_Description(std::make_unique<Text>(description, 400.0f, 235.0f, 12.0f, 0.0f)),
			m_Button(std::make_unique<Button>(0.0f, 0.0f, 180, 50, button)),
			m_Fade(std::make_unique<Rectangle>(400.0f, 300.0f, 800.0f, 600.0f))
		{
			m_Description->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_Fade->SetColor(0.0f, 0.0f, 0.0f, 0.95f);
		}
		int m_ActivityCoolDown, m_ActivityReady;
		bool m_Exit;
		std::unique_ptr<Text> m_Description;
		std::unique_ptr<Button> m_Button;
		std::unique_ptr<Rectangle> m_Fade;
	};

	class GatherResources : public BaseScene
	{
	public:
		GatherResources();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "Gather Resources"; }
	private:
		enum class Activity {MENU, CHOP, MINE, FARM, EXPLORE};
		Vec4i m_AmountGathered;
		Activity m_CurrentActivity;
		std::unique_ptr<Button> m_Chop, m_Mine, m_Farm, m_Explore, m_BackToCamp;
		std::unique_ptr<Text> m_Text;
	};

	class Rest : public BaseScene
	{
	public:
		Rest();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "Rest"; }
	private:
		std::unique_ptr<Text> m_RestText;
		std::unique_ptr<Button> m_Confirm, m_Cancel;
	};

	class Library : public BaseScene
	{
	public:
		Library();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "Library"; }
	private:
		std::unique_ptr<TowerDefense::CardChoice> m_CardChoice;
		std::unique_ptr<Button> m_Confirm, m_Cancel;
	};

	class Smithing : public BaseScene
	{
	public:
		Smithing();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "Smithing"; }
	private:
		void FindSelectedCard();

		std::shared_ptr<Card> m_SelectedCard, m_SelectedCardImage;
		std::unique_ptr<TowerDefense::StaticImage> m_SmithingArrow;
		std::unique_ptr<Button> m_Confirm, m_Cancel;
	};

	class Tavern : public BaseScene
	{
	public:
		Tavern();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "Tavern"; }
	private:
		bool m_HeroTaken;
		std::unique_ptr<TowerDefense::CardChoice> m_TavernChoice;
		std::unique_ptr<Button> m_Confirm, m_Cancel;
	};

	class Chapel : public BaseScene
	{
	public:
		Chapel();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "Chapel"; }
	private:
		void FindSelectedCard();

		int m_Index;
		std::unique_ptr<Text> m_RemoveText;
		std::shared_ptr<Card> m_SelectedCard;
		std::unique_ptr<Button> m_Confirm, m_Cancel;
	};

	class Build : public BaseScene
	{
	public:
		Build();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "Build"; }
	private:
		void AddBuildButton(std::shared_ptr<BuildButton> button);
		bool HasResources(std::shared_ptr<BuildButton> b);

		std::unique_ptr<Button> m_Cancel;
		std::unique_ptr<std::vector<std::shared_ptr<BuildButton>>> m_Buttons;
	};

	class Trader : public BaseScene
	{
	public:
		Trader();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "Trader"; }
	private:
		void FindInfo();

		int m_InfoCard, m_InfoArtifact, m_SpinEnd;
		std::array<std::unique_ptr<CardSlot>, 6> m_Cards;
		std::array<std::unique_ptr<ArtifactSlot>, 3> m_Artifacts;
		std::unique_ptr<Button> m_Wood, m_Stone, m_Wheat, m_Spin, m_BackToCamp;
		std::unique_ptr<Text> m_WoodText, m_StoneText, m_WheatText, m_SpinText;
		std::unique_ptr<Image> m_WoodGoldIcon, m_StoneGoldIcon, m_WheatGoldIcon, m_SpinGoldIcon, m_SpinWheel, m_SpinPicker;
	};

	class ManageWorkers : public BaseScene
	{
	public:
		ManageWorkers();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "ManageWorkers"; }

	private:
		std::unique_ptr<Button> m_BackToCamp, m_WoodPlus, m_WoodAddAll, m_WoodMinus, m_WoodMinusAll, 
			m_StonePlus, m_StoneMinus, m_StoneAddAll, m_StoneMinusAll, m_WheatPlus, m_WheatMinus, m_WheatAddAll,
			m_WheatMinusAll, m_BuildHouse, m_HireWorker;
		std::unique_ptr<Text> m_HouseText, m_TotalText, m_AvailableText, m_LumberjacksText, m_MinersText, m_FarmersText, 
			m_BuildCost, m_WorkerCost, m_TotalPopText, m_AvailablePopText, m_NumLumberJacks, m_NumMiners, m_NumFarmers;
		std::unique_ptr<Image> m_HouseImage, m_WorkerImage, m_WorkerAvailableImage, m_WoodImage, m_StoneImage, m_WheatImage;
	};

	class Joust : public BaseScene
	{
	public:
		Joust();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "Joust"; }

	private:
		int m_Distance, m_Winner, m_Level, m_CircleSpawn;

		bool m_Jousting, m_Failed;

		std::unique_ptr<Button> m_BackToCamp, m_Joust;

		std::unique_ptr<Image> m_Player, m_Knight;

		std::unique_ptr<Text> m_WinnerMessage, m_LevelText;

		std::vector<ClickCircle> m_Circles;
		std::vector<int> m_RemoveCircles;
	};

	class ArcheryRange : public BaseScene
	{
	public:
		ArcheryRange();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "ArcheryRange"; }

	private:
		std::unique_ptr<Button> m_BackToCamp;
	};

	class WizardTower : public BaseScene
	{
	public:
		WizardTower();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "WizardTower"; }

	private:
		std::unique_ptr<Button> m_BackToCamp;
	};

	class Temple : public BaseScene
	{
	public:
		Temple();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "Temple"; }

	private:
		std::unique_ptr<Button> m_BackToCamp;
	};

	class AlchemyLab : public BaseScene
	{
	public:
		AlchemyLab();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "AlchemyLab"; }

	private:
		std::unique_ptr<Button> m_BackToCamp;
	};

	class MusicHall : public BaseScene
	{
	public:
		MusicHall();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "MusicHall"; }

	private:
		std::unique_ptr<Button> m_BackToCamp;
	};
}
