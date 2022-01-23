#pragma once
#include "Scene.h"
#include "random_events/RandomEvent.h"
#include "InGameSettings.h"

namespace TowerDefense
{
	class Event : public Scene
	{
	public:
		Event();
		void Render() override;
		void Update() override;
		void OnSwitch() override;

	private:

		enum class EventPhase {START, EVENT, END};

		float m_TransitionFade, m_FadeSpeed;

		EventPhase m_Phase, m_NextPhase;

		std::unique_ptr<Text> m_EventText, m_EventQuestionMark;

		std::unique_ptr<Button> m_Continue;

		std::shared_ptr<RandomEvent> m_RandomEvent;
	};
}