#include "pch.h"
#include "Hand.h"
#include "TowerDefense.h"
#include "core/Player.h"

TowerDefense::Hand::Hand(unsigned int maxSize)
	:m_MaxSize(maxSize), m_CardSpacing(0), m_SelectedCard(-1), m_CardsToDiscard(0), 
	m_CardsToExhaust(0), m_Dragging(false), m_ShowingInfo(false), 
	m_Cards(std::make_unique<std::vector<std::shared_ptr<Card>>>()),
	m_SelectedCards(std::make_unique<std::vector<int>>()),
	m_Fade(std::make_unique<Rectangle>(400.0f, 300.0f, 800.0f, 600.0f))
{
	m_Fade->SetColor(0.0f, 0.0f, 0.0f, 0.9f);
}

void TowerDefense::Hand::Render()
{
	if (m_CardsToDiscard != 0 || m_CardsToExhaust != 0)
	{
		m_Fade->Render();
		m_SelectionText->Render();
	}

	for (unsigned int i = 0; i < m_Cards->size(); i++)
	{
		if (i != m_SelectedCard)
		{
			m_Cards->at(i)->Render();
			if(CardSelected(i) != -1)
				m_Cards->at(i)->RenderOutline();
		}
	}
	
	//Render selected card afterwards to ensure it is on top of other cards
	if (m_SelectedCard != -1)
	{
		m_Cards->at(m_SelectedCard)->Render();
		if (CardSelected(m_SelectedCard) != -1)
			m_Cards->at(m_SelectedCard)->RenderOutline();
	}
		

	if (m_ShowingInfo)
	{
		m_Fade->Render();
		m_Cards->at(m_SelectedCard)->RenderCardDetails();
	}
}

void TowerDefense::Hand::Update()
{
	Player& player = Player::Get();
	//Update Position of Selected Card and Check if Dropped
	if (m_SelectedCard != -1)
	{
		if (m_Dragging)
		{
			m_Cards->at(m_SelectedCard)->SetX((float)Input::GetMouseX());
			m_Cards->at(m_SelectedCard)->SetY((float)Input::GetMouseY());
			m_Cards->at(m_SelectedCard)->Update();
			if (!Input::GetLeftMouseClicked())
			{
				m_Dragging = false;
				if (Input::GetMouseY() > 600.0f * .35f)
				{
					if (player.GetEnergy() >= m_Cards->at(m_SelectedCard)->GetCost())
					{
						if (m_Cards->at(m_SelectedCard)->Play())
						{
							player.ChangeEnergy(0 - m_Cards->at(m_SelectedCard)->GetCost());
							std::shared_ptr<Card> c = Player::Get().GetHand()->RemoveCard(m_Cards->at(m_SelectedCard)->GetHandPosition());
							player.ArtifactOnCardPlay(c);
							if (!c->Exhausts())
								player.GetDiscardPile()->AddCard(c);
						}
					}
					else
						m_Cards->at(m_SelectedCard)->SetOverBoard(false);
				}
			}
		}
		else
		{
			float power = 3.0f;
			if (m_Cards->size() > 6)
				power = 2.5;
			m_Cards->at(m_SelectedCard)->SetX(400.0f + (m_Cards->at(m_SelectedCard)->GetHandPosition() - (m_Cards->size() - 1) / 2.0f) * m_CardSpacing);
			m_Cards->at(m_SelectedCard)->SetY(90.0f - pow(abs(m_Cards->at(m_SelectedCard)->GetHandPosition() - (m_Cards->size() - 1) / 2.0f), power));
			m_Cards->at(m_SelectedCard)->SetRotation(0.0f - (m_Cards->at(m_SelectedCard)->GetHandPosition() - (m_Cards->size() - 1) / 2.0f) * 5);
		
			if (Input::GetRightMouseClickedAndSetFalse())
				m_ShowingInfo = true;
		}
	}

	if (!m_Dragging && !m_ShowingInfo)
		FindSelectedCard();

	if ((m_CardsToDiscard != 0 && m_CardsToDiscard == m_SelectedCards->size()) || (m_CardsToExhaust != 0 && m_CardsToExhaust == m_SelectedCards->size()))
	{
		std::sort(m_SelectedCards->begin(), m_SelectedCards->end());
		for (int i = m_SelectedCards->size() - 1; i > -1; i--)
		{
			if(m_CardsToDiscard != 0)
				Player::Get().GetDiscardPile()->AddCard(m_Cards->at(m_SelectedCards->at(i)));
			RemoveCard(m_SelectedCards->at(i));
		}

		m_CardsToDiscard = 0;
		m_CardsToExhaust = 0;
		m_SelectedCards->clear();
	}

	if (m_ShowingInfo && (Input::GetRightMouseClickedAndSetFalse() || Input::GetLeftMouseClickedAndSetFalse()))
	{
		m_ShowingInfo = false;
		m_SelectedCard = -1;
	}	
}

void TowerDefense::Hand::FindSelectedCard()
{
	m_SelectedCard = -1;
	for (unsigned int i = 0; i < m_Cards->size(); i++) {
		if (m_Cards->at(i)->Contains(Input::GetMouseX(), (float)Input::GetMouseY())) {
			m_SelectedCard = i;
			m_Cards->at(i)->SetRotation(0);
			if (Input::GetLeftMouseClicked()) {
				if(m_CardsToDiscard == 0 && m_CardsToExhaust == 0)
					m_Dragging = true;
				else
				{
					Input::GetLeftMouseClickedAndSetFalse();
					int index = CardSelected(i);
					if (index == -1)
						m_SelectedCards->push_back(i);
					else
						m_SelectedCards->erase(m_SelectedCards->begin() + index);
				}
			}
			break;
		}
	}
}

void TowerDefense::Hand::AddCard(std::shared_ptr<Card> c)
{
	if (m_Cards->size() < m_MaxSize) {
		c->SetHandPosition(m_Cards->size());
		m_Cards->push_back(c);
		UpdateSpacing();
	}
	else
		Player::Get().GetDiscardPile()->AddCard(c);
}

std::shared_ptr<TowerDefense::Card> TowerDefense::Hand::RemoveCard(int index)
{
	std::shared_ptr<Card> c = m_Cards->at(index);
	m_Cards->erase(m_Cards->begin()+index);

	for (unsigned int i = 0; i < m_Cards->size(); i++) {
		m_Cards->at(i)->SetHandPosition(i);
	}

	if (m_SelectedCard == index)
		m_SelectedCard = -1;

	UpdateSpacing();
	return c;
}

void TowerDefense::Hand::UpdateSpacing()
{
	//Determine Spacing between Cards
	if (m_Cards->size() == 0)
		return;
	if (m_Cards->size() > 5)
		m_CardSpacing = (int)(50 + 900 / (pow(m_Cards->size(), 2)));
	else
		m_CardSpacing = 80;

	//Set x, y, and rotation of nonselected cards based on spacing
	float power = 3.0f;
	if (m_Cards->size() > 6)
		power = 2.5;
	for (unsigned int i = 0; i < m_Cards->size(); i++) {
		m_Cards->at(i)->SetRotation(0.0f - (m_Cards->at(i)->GetHandPosition() - (m_Cards->size() - 1) / 2.0f) * 5);
		if (i != m_SelectedCard) {
			m_Cards->at(i)->SetX(400.0f + (m_Cards->at(i)->GetHandPosition() - (m_Cards->size() - 1) / 2.0f) * m_CardSpacing);
			m_Cards->at(i)->SetY(90.0f - pow(abs((m_Cards->at(i)->GetHandPosition() - (m_Cards->size() - 1) / 2.0f)), power));
		}
	}
}

void TowerDefense::Hand::DrawCard()
{
	auto drawPile = Player::Get().GetDrawPile();
	auto discardPile = Player::Get().GetDiscardPile();

	//Shuffle in discard pile if draw pile is empty
	if (drawPile->GetSize() == 0) {

		discardPile->Transfer(drawPile);
		drawPile->Shuffle();
	}

	//Draw top card from drawpile
	if (drawPile->GetSize() > 0)
	{
		auto c = drawPile->RemoveCard(0);
		if (c)
		{
			if (m_Cards->size() < m_MaxSize + 1)
				AddCard(c);
			else
				discardPile->AddCard(c);
		}
	}	
}

void TowerDefense::Hand::DiscardHand()
{
	while (m_Cards->size() > 0) {
		Player::Get().GetDiscardPile()->AddCard(m_Cards->at(0));
		RemoveCard(0);
	}
}

void TowerDefense::Hand::DiscardCards(int numDiscard) 
{ 
	m_CardsToDiscard = numDiscard; 
	if ((int)m_Cards->size() < m_CardsToDiscard)
		m_CardsToDiscard = m_Cards->size();
	m_SelectionText = std::make_unique<Text>("Select " + std::to_string(m_CardsToDiscard) + " Cards to Discard", 400.0f, 300.0f, 16.0f, 0.0f);
	m_SelectionText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
};

void TowerDefense::Hand::ExhaustCards(int numExhaust)
{
	m_CardsToExhaust = numExhaust;
	if ((int)m_Cards->size() < m_CardsToExhaust)
		m_CardsToExhaust = m_Cards->size();
	m_SelectionText = std::make_unique<Text>("Select " + std::to_string(m_CardsToExhaust) + " Cards to Exhaust", 400.0f, 300.0f, 16.0f, 0.0f);
	m_SelectionText->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
};

int TowerDefense::Hand::CardSelected(int card)
{
	for (unsigned int j = 0; j < m_SelectedCards->size(); j++)
	{
		if (m_SelectedCards->at(j) == card)
			return j;
	}
	return -1;
}