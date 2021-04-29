#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"

TowerDefense::Chapel::Chapel()
	:BaseScene("prayButton", "Forgive your mistakes."),
	m_Index(-1),
	m_RemoveText(std::make_unique<Text>("Remove Card?", 400.0f, 140.0f, 12.0f, 0.0f)),
	m_Confirm(std::make_unique<Button>(400.0f, 190.0f, 180, 50, "confirmButton")),
	m_Cancel(std::make_unique<Button>(690.0f, 125.0f, 180, 50, "cancelButton"))
{
	m_RemoveText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TowerDefense::Chapel::Render()
{
	Player& player = Player::Get();
	player.RenderDeck();

	if (m_SelectedCard)
	{
		m_Fade->Render();
		m_SelectedCard->Render();
		m_Confirm->Render();
		m_RemoveText->Render();
	}

	if(!player.GetSelectedDeckCard())
		m_Cancel->Render();
}

void TowerDefense::Chapel::Update()
{
	Player& player = Player::Get();
	if (m_SelectedCard)
	{
		m_Confirm->Update();
		if (m_Confirm->IsClicked())
		{
			m_ActivityDone = true;
			m_Exit = true;
			player.ShowDeck(false);
			player.RemoveFromDeck(m_Index);
		}
		if (!player.GetSelectedDeckCard())
		{
			m_Cancel->Update();
			if (m_Cancel->IsClicked())
			{
				m_SelectedCard.reset();
				m_Index = -1;
			}
		}
	}
	else if (!player.GetSelectedDeckCard())
	{
		m_Cancel->Update();
		if (m_Cancel->IsClicked())
		{
			m_Exit = true;
			player.ShowDeck(false);
		}
	}

	if (!m_SelectedCard)
	{
		if (!player.GetSelectedDeckCard())
			FindSelectedCard();
		if (!m_SelectedCard)
			player.UpdateDeck();
	}
}

void TowerDefense::Chapel::OnSwitch()
{
	BaseScene::OnSwitch();
	Player::Get().ShowDeck(true);
	m_SelectedCard.reset();
	m_Index = -1;
}

void TowerDefense::Chapel::FindSelectedCard()
{
	if (!Input::GetLeftMouseClicked())
		return;

	auto card = Player::Get().GetClickedDeckCard();
	if (card)
	{
		m_SelectedCard = card->Clone();
		m_SelectedCard->SetX(400);
		m_SelectedCard->SetY(300);

		m_Index = Player::Get().GetCardIndex(card);
	}
}