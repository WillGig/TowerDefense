#include "pch.h"
#include "Event.h"
#include "TowerDefense.h"
#include "core/Player.h"

TowerDefense::Event::Event()
	:m_Phase(EventPhase::START), m_EventText(std::make_unique<Text>("EVENT", 400.0f, 450.0f, 50.0f, 0.0f)),
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
	else if (m_Phase == EventPhase::EVENT)
	{
		Player::Get().RenderStats();
		m_RandomEvent->Render();
		Player::Get().RenderDeckAndArtifacts();
	}
}

void TowerDefense::Event::Update()
{
	if (m_Phase == EventPhase::START)
	{
		m_Continue->Update();
		if (m_Continue->IsClicked())
			m_Phase = EventPhase::EVENT;
	}
	else if (m_Phase == EventPhase::EVENT)
	{
		Player& player = Player::Get();
		player.UpdateDeckAndArtifacts();

		if (!player.DeckShowing() && !player.ArtifactsShowing())
		{
			m_RandomEvent->Update();
			if (m_RandomEvent->Exit())
				SetScene(SceneType::PRECOMBAT);
		}
	}
}

void TowerDefense::Event::OnSwitch()
{
	m_Phase = EventPhase::START;
	m_RandomEvent = RandomEvent::GetRandomCaveEvent();
}
