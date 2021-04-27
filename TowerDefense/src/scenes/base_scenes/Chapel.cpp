#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"

TowerDefense::Chapel::Chapel()
	:BaseScene("prayButton", "Forgive your mistakes."),
	m_Index(-1),
	m_Confirm(std::make_unique<Button>(400.0f, 190.0f, 180, 50, "confirmButton")),
	m_Cancel(std::make_unique<Button>(690.0f, 125.0f, 180, 50, "cancelButton"))
{
}

void TowerDefense::Chapel::Render()
{
	auto deck = Player::Get().GetDeck();
	deck->RenderCards();

	if (m_SelectedCard)
	{
		m_Fade->Render();
		if (!deck->GetSelectedCard())
			m_Cancel->Render();
		m_SelectedCard->Render();
		m_Confirm->Render();
	}
	else if (!deck->GetSelectedCard())
	{
		m_Cancel->Render();
	}
}

void TowerDefense::Chapel::Update()
{
	auto deck = Player::Get().GetDeck();
	if (m_SelectedCard)
	{
		m_Confirm->Update();
		if (m_Confirm->IsClicked())
		{
			m_ActivityDone = true;
			m_Exit = true;
			deck->Show(false);
			deck->RemoveCard(m_Index);
		}
		if (!deck->GetSelectedCard())
		{
			m_Cancel->Update();
			if (m_Cancel->IsClicked())
			{
				m_SelectedCard.reset();
				m_Index = -1;
			}
		}
	}
	else if (!deck->GetSelectedCard())
	{
		m_Cancel->Update();
		if (m_Cancel->IsClicked())
		{
			m_Exit = true;
			deck->Show(false);
		}
	}

	if (!m_SelectedCard)
	{
		if (!deck->GetSelectedCard())
			FindSelectedCard();
		if (!m_SelectedCard)
			deck->Update();
	}
}

void TowerDefense::Chapel::OnSwitch()
{
	BaseScene::OnSwitch();
	Player::Get().GetDeck()->Show(true);
	m_SelectedCard.reset();
	m_Index = -1;
}

void TowerDefense::Chapel::FindSelectedCard()
{
	if (!Input::GetLeftMouseClicked())
		return;

	auto deck = Player::Get().GetDeck();
	auto card = deck->GetClickedCard();
	if (card)
	{
		m_SelectedCard = card->Clone();
		m_SelectedCard->SetX(400);
		m_SelectedCard->SetY(300);

		for (int i = 0; i < (int)deck->GetSize(); i++)
		{
			if (deck->GetCard(i) == card)
			{
				m_Index = i;
				break;
			}
		}
	}
}