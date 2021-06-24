#include "pch.h"
#include "SideboardSlot.h"
#include "Card.h"
#include "core/Player.h"

TowerDefense::SideboardSlot::SideboardSlot()
	:Entity(0.0f, 0.0f, 55, 70, 0.0f, "SideboardSlot", Type::CARDPILE), m_SelectingCard (false), m_Card(0)
{}

void TowerDefense::SideboardSlot::Update()
{
	Player& player = Player::Get();
	if (m_SelectingCard)
	{
		if (!player.GetSelectedDeckCard())
		{
			auto c = player.GetClickedDeckCard();
			if (c)
			{
				m_Card = c->GetID();
				SetImage(std::make_shared<Image>(c->GetImageName(), m_X, m_Y, m_Width, m_Height, 0.0f));
				m_SelectingCard = false;
				player.ShowDeck(false);
			}
		}
		player.UpdateDeck();
	}
	else
	{
		if (Contains(Input::GetMouseX(), Input::GetMouseY()) && Input::GetLeftMouseClickedAndSetFalse())
		{
			m_SelectingCard = true;
			player.ShowDeck(true);
			player.UpdateDeck();
		}
	}
}

void TowerDefense::SideboardSlot::Render()
{
	if (m_SelectingCard)
	{
		Player::Get().RenderDeck();
		Player::Get().GetSelectedDeckCard();
	}
	else
		Entity::Render();
}

void TowerDefense::SideboardSlot::Clear()
{
	m_SelectingCard = false;
	m_Card = 0;
	SetImage(std::make_shared<Image>("SideboardSlot", m_X, m_Y, m_Width, m_Height, 0.0f));
}