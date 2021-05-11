#pragma once
#include "scenes/Scene.h"
#include "scenes/cave_scenes/CaveScene.h"
#include "cards/CardChoice.h"
#include "BuildButton.h"

namespace TowerDefense
{
	class BuildButton;

	class BaseScene : public Scene
	{
	public:
		inline bool ActivityDone() const { return m_ActivityDone; }
		inline void SetActivityDone(bool done) { m_ActivityDone = done; }
		inline bool Exit() const { return m_Exit; }
		inline void RenderButton() { m_Button->Render(); }
		inline void UpdateButton() { m_Button->Update(); }
		inline bool ButtonClicked() const { return m_Button->IsClicked(); }
		inline bool ButtonSelected() const { return m_Button->IsSelected(); }
		inline void SetButtonPosition(float x, float y) { m_Button->SetX(x); m_Button->SetY(y); }
		inline void RenderText() { m_Description->Render(); }
		inline void OnSwitch() override { m_Exit = false; m_Button->SetSelected(false); };
		virtual std::string GetName() = 0;
	protected:
		BaseScene(const std::string& button, const std::string& description)
			:m_Exit(false), m_ActivityDone(false), m_Description(std::make_unique<Text>(description, 400.0f, 235.0f, 12.0f, 0.0f)),
			m_Button(std::make_unique<Button>(0.0f, 0.0f, 180, 50, button)),
			m_Fade(std::make_unique<Rectangle>(400.0f, 300.0f, 800.0f, 600.0f))
		{
			m_Description->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_Fade->SetColor(0.0f, 0.0f, 0.0f, 0.95f);
		}
		bool m_Exit, m_ActivityDone;
		std::unique_ptr<Text> m_Description;
		std::unique_ptr<Button> m_Button;
		std::unique_ptr<Rectangle> m_Fade;
	};

	class Caves : public BaseScene
	{
	public:
		Caves();
		void Render() override;
		void Update() override;
		void OnSwitch() override;
		inline std::string GetName() override { return "Caves"; }
	private:
		enum class Activity {MENU, EXPLORE, MINE};
		int m_GoldMined;
		Activity m_CurrentActivity;
		std::unique_ptr<Button> m_Explore, m_Mine, m_BackToCamp;
		std::unique_ptr<Text> m_MiningText;
		std::shared_ptr<CaveScene> m_CaveScene;
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
}
