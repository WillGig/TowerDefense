#include "pch.h"
#include "CardPile.h"
#include "TowerDefense.h"

TowerDefense::CardPile::CardPile(float x, float y)
	:Entity(x, y, 66, 84, 0.0f, "deckFull", TowerDefense::Type::CARDPILE),
	m_Scroll(0), m_SelectedCard(-1), m_Showing(false), m_Ordered(true), 
	m_Cards(std::make_unique<std::vector<std::shared_ptr<Card>>>()), m_RandomOrder(),
	m_FullImage(std::make_shared<Image>("deckFull", x, y, 66, 84, 0.0f)),
	m_EmptyImage(std::make_shared<Image>("deckEmpty", x, y, 66, 84, 0.0f)),
	m_Fade(std::make_unique<Rectangle>(400.0f, 300.0f, 800.0f, 600.0f))
{
	m_Fade->SetColor(0.0f, 0.0f, 0.0f, 0.9f);
}

void TowerDefense::CardPile::Update()
{
	//If clicked toggle show
	if (Contains((float)Input::GetMouseX(), (float)Input::GetMouseY()) && Input::GetLeftMouseClickedAndSetFalse())
		Show(!m_Showing);

	if (m_Showing) {
		if (m_SelectedCard == -1)
		{
			m_Scroll -= Input::GetMouseSCROLL() * 30;
			if (m_Scroll < 0)
				m_Scroll = 0;
			else if (m_Scroll > ((int)m_Cards->size() / 5 - 1) * 165)
			{
				//Set maximum scroll
				m_Scroll = (int)(((int)m_Cards->size() / 5 - 1) * 165);
				//Disable scrolling with less than 5 cards
				if (m_Cards->size() < 5)
					m_Scroll = 0;
			}
		}

		//Update Card position based on scrolling
		//Check for Selected Card
		for (int i = 0; i < (int)m_Cards->size(); i++) {
			if (m_Ordered) 
			{
				m_Cards->at(i)->SetY(500.0f - 165 * (i / 5) + m_Scroll);
				m_Cards->at(i)->SetX(400.0f - ((i / 5) * 5 + 2 - i) * 135.0f);
			}
			else
			{
				m_Cards->at(m_RandomOrder[i])->SetY(500.0f - 165 * (i / 5) + m_Scroll);
				m_Cards->at(m_RandomOrder[i])->SetX(400.0f - ((i / 5) * 5 + 2 - i) * 135.0f);
			}

			//Check for Selected Card
			if (m_SelectedCard != -1)
				continue;
			if (m_Cards->at(i)->Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetRightMouseClickedAndSetFalse())
				m_SelectedCard = i;
		}

		if (m_SelectedCard != -1 && Input::GetRightMouseClickedAndSetFalse() || Input::GetLeftMouseClickedAndSetFalse())
			m_SelectedCard = -1;
	}
}

void TowerDefense::CardPile::RenderCards()
{
	m_Fade->Render();
	for (unsigned int i = 0; i < m_Cards->size(); i++) {
		m_Cards->at(i)->Render();
	}
	if (m_SelectedCard != -1)
	{
		m_Fade->Render();
		m_Cards->at(m_SelectedCard)->RenderCardDetails();
	}
}

void TowerDefense::CardPile::AddCard(std::shared_ptr<Card> c)
{
	c->SetRotation(0.0f);
	m_Cards->push_back(c);
	Randomize();
	if (m_Cards->size() == 1)
		SetImage(m_FullImage);
}

std::shared_ptr<TowerDefense::Card> TowerDefense::CardPile::RemoveCard(int index)
{
	std::shared_ptr<Card> returner = m_Cards->at(index);
	m_Cards->erase(m_Cards->begin() + index);
	Randomize();
	if (m_Cards->size() == 0)
		SetImage(m_EmptyImage);
	return returner;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::CardPile::GetSelectedCard()
{
	if (m_SelectedCard == -1)
		return nullptr;
	return m_Cards->at(m_SelectedCard);
}

std::shared_ptr<TowerDefense::Card> TowerDefense::CardPile::GetClickedCard()
{
	for (unsigned int i = 0; i < m_Cards->size(); i++)
	{
		if (m_Cards->at(i)->Contains(Input::GetMouseX(), Input::GetMouseY()))
		{
			if (Input::GetLeftMouseClickedAndSetFalse())
				return m_Cards->at(i);
		}
	}
	return nullptr;
}

//Transfers current pile to pile p
void TowerDefense::CardPile::Transfer(std::shared_ptr<CardPile> p)
{
	for (unsigned int i = 0; i < m_Cards->size(); i++)
		p->AddCard(m_Cards->at(i));
	m_Cards->clear();
	SetImage(m_EmptyImage);
}

//Clears p and copies a clone of all of the cards in the current pile into p
void TowerDefense::CardPile::Copy(std::shared_ptr<CardPile> p)
{
	p->Clear();
	for (unsigned int i = 0; i < m_Cards->size(); i++)
	{
		p->AddCard(m_Cards->at(i)->Clone());
	}
		
}

void TowerDefense::CardPile::Clear()
{
	m_Cards->clear();
	SetImage(m_EmptyImage);
}

//Randomly swaps cards to get a random order
void TowerDefense::CardPile::Shuffle()
{
	Randomize();
	for (unsigned int i = 0; i < m_Cards->size() * 2; i++) {
		Swap((int)(Random::GetFloat() * m_Cards->size()), (int)(Random::GetFloat() * m_Cards->size()));
	}
}

void TowerDefense::CardPile::Swap(int i, int j)
{
	std::shared_ptr<Card> temp = m_Cards->at(i);
	m_Cards->at(i) = m_Cards->at(j);
	m_Cards->at(j) = temp;
}

//sets m_RandomOrder to a new vector of ints from 0 to m_Cards.size() in a random order
void TowerDefense::CardPile::Randomize()
{
	std::vector<int> numbers;
	for (unsigned int i = 0; i < m_Cards->size(); i++)
		numbers.push_back(i);

	m_RandomOrder = std::vector<int>();
	for (unsigned int i = 0; i < m_Cards->size(); i++) {
		int index = (int)(Random::GetFloat() * numbers.size());
		m_RandomOrder.push_back(numbers[index]);
		numbers.erase(numbers.begin() + index);
	}
}