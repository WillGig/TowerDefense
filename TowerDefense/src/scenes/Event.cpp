#include "pch.h"
#include "Event.h"
#include "TowerDefense.h"
#include "core/Player.h"

TowerDefense::Event::Event()
	:m_TransitionFade(1.0f), m_FadeSpeed(0.05f), 
	m_Phase(EventPhase::START), m_NextPhase(EventPhase::START),
	m_EventText(std::make_unique<Text>("EVENT", 400.0f, 450.0f, 50.0f, 0.0f)),
	m_EventQuestionMark(std::make_unique<Text>("?", 400.0f, 300.0f, 100.0f, 0.0f)),
	m_Continue(std::make_unique<Button>(400.0f, 150.0f, 180, 50, "continueButton"))
{
	m_EventText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_EventQuestionMark->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::Event::Render()
{
	if (m_Phase == EventPhase::START)
	{
		m_EventText->Render();
		m_EventQuestionMark->Render();
		m_Continue->Render();
	}
	else
	{
		Player::Get().RenderStats();
		InGameSettings::Get().RenderButton();
		
		if(m_Phase == EventPhase::EVENT)
			m_RandomEvent->Render();
		else if (m_Phase == EventPhase::END)
		{
			m_RandomEvent->RenderEnd();
			m_Continue->Render();
		}

		if(!m_RandomEvent->ShowingInfo())
			Player::Get().RenderDeckAndArtifacts();

		if (InGameSettings::Get().IsShowing())
			InGameSettings::Get().Render();
	}

	if (m_TransitionFade > 0.0f)
		RenderFade(m_TransitionFade);
}

void TowerDefense::Event::Update()
{
	if (InGameSettings::Get().IsShowing())
	{
		InGameSettings::Get().Update();
		return;
	}

	if (m_Phase == EventPhase::START)
	{
		m_Continue->Update();
		if (m_Continue->IsClicked())
			m_NextPhase = EventPhase::EVENT;
	}
	else
	{
		if (m_RandomEvent->ShowingInfo())
		{
			m_RandomEvent->Update();
			return;
		}

		Player& player = Player::Get();
		player.UpdateDeckAndArtifacts();

		if (!player.DeckShowing() && !player.ArtifactsShowing())
		{
			InGameSettings::Get().UpdateButton();

			if (m_Phase == EventPhase::EVENT)
			{
				if(m_Phase == m_NextPhase)
					m_RandomEvent->Update();
				if (m_RandomEvent->Exit())
					m_NextPhase = EventPhase::END;
			}
			else if (m_Phase == EventPhase::END)
			{
				m_Continue->Update();
				if (m_Continue->IsClicked())
					SetScene(SceneType::PRECOMBAT);
			}
		}
	}

	if (m_NextPhase != m_Phase)
	{
		if (m_TransitionFade < 1.0f)
			m_TransitionFade += m_FadeSpeed;
		else
			m_Phase = m_NextPhase;
	}
	else if (m_TransitionFade > 0.0f)
		m_TransitionFade -= m_FadeSpeed;
}

void TowerDefense::Event::OnSwitch()
{
	m_Phase = EventPhase::START;
	m_RandomEvent = RandomEvent::GetRandomEvent();
}
