#include "pch.h"
#include "CardChoice.h"

//Chooses random cards and arranges them evenly in the center of the screen
TowerDefense::CardChoice::CardChoice(int numCards, int generationDay)
	:m_SelectedCard(-1), m_InfoCard(-1), m_GenerationDay(generationDay),
	m_Cards(std::make_shared<std::vector<std::shared_ptr<Card>>>()), 
	m_Outline(std::make_unique<Image>("outline", 0.0f, 0.0f, 116, 146, 0.0f)),
	m_Fade(std::make_unique<Rectangle>(400.0f, 300.0f, 800.0f, 600.0f))
{
	m_Fade->SetColor(0.0f, 0.0f, 0.0f, 0.9f);
	for (int i = 0; i < numCards; i++)
	{
		std::shared_ptr<Card> c = PickACard();
		c->SetX(400.0f + (i - ((float)numCards - 1.0f) / 2.0f) * 140);
		c->SetY(300.0f);
		m_Cards->push_back(c);
	}
}

//Uses specific card list and arranges them evenly in the center of the screen
TowerDefense::CardChoice::CardChoice(std::shared_ptr<std::vector<std::shared_ptr<Card>>> cards, int generationDay)
	:m_SelectedCard(-1), m_InfoCard(-1), m_GenerationDay(generationDay), m_Cards(cards), 
	m_Outline(std::make_unique<Image>("outline", 0.0f, 0.0f, 116, 146, 0.0f)),
	m_Fade(std::make_unique<Rectangle>(400.0f, 300.0f, 800.0f, 600.0f))
{
	m_Fade->SetColor(0.0f, 0.0f, 0.0f, 0.9f);
	for (int i = 0; i < (int)cards->size(); i++)
	{
		m_Cards->at(i)->SetX(400.0f + (i - ((float)cards->size() - 1.0f) / 2.0f) * 140);
		m_Cards->at(i)->SetY(300.0f);
	}
}

void TowerDefense::CardChoice::Update()
{
	for (unsigned int i = 0; i < m_Cards->size(); i++)
	{
		if (m_Cards->at(i)->Contains(Input::GetMouseX(), Input::GetMouseY()))
		{
			if (m_InfoCard == -1 && Input::GetLeftMouseClickedAndSetFalse())
			{
				m_SelectedCard = i;
				m_Outline->SetPosition(m_Cards->at(i)->GetX(), m_Cards->at(i)->GetY(), 0.0f);
			}
			else if (m_InfoCard == -1 && Input::GetRightMouseClickedAndSetFalse())
			{
				m_InfoCard = i;
			}
		}
	}

	if (Input::GetLeftMouseClickedAndSetFalse() || Input::GetRightMouseClickedAndSetFalse())
		m_InfoCard = -1;
}

void TowerDefense::CardChoice::Render()
{
	for (unsigned int i = 0; i < m_Cards->size(); i++)
		m_Cards->at(i)->Render();

	if (m_InfoCard != -1)
	{
		m_Fade->Render();
		m_Cards->at(m_InfoCard)->RenderCardDetails();
	}
	else if (m_SelectedCard != -1)
		m_Outline->Render();
}

std::shared_ptr<TowerDefense::Card> TowerDefense::CardChoice::GetSelectedCard() const
{
	if (m_SelectedCard == -1)
		return nullptr;
	return m_Cards->at(m_SelectedCard);
}

void TowerDefense::CardChoice::RemoveSelectedCard()
{
	if (m_SelectedCard == -1)
		return;
	m_Cards->erase(m_Cards->begin() + m_SelectedCard);
	m_SelectedCard = -1;
}

//Chooses a random card based on preset rarity chances
std::shared_ptr<TowerDefense::Card> TowerDefense::CardChoice::PickACard()
{
	float chance = Random::GetFloat();

	if (chance < Card::GetRareChance())
		return Card::GetRareCard();
	else if (chance < Card::GetRareChance() + Card::GetUncommonChance())
		return Card::GetUncommonCard();
	else
		return Card::GetCommonCard();
}