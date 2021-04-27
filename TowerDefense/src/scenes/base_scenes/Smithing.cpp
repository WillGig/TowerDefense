#include "pch.h"
#include "BaseScene.h"
#include "core/Player.h"
#include "cards/HeroCard.h"

TowerDefense::Smithing::Smithing()
	:BaseScene("smithButton", "Upgrade!"),
	m_SmithingArrow(std::make_unique<StaticImage>(400.0f, 300.0f, 36, 36, 0.0f, "smithArrow")),
	m_Confirm(std::make_unique<Button>(400.0f, 190.0f, 180, 50, "confirmButton")),
	m_Cancel(std::make_unique<Button>(690.0f, 125.0f, 180, 50, "cancelButton"))
{
}

void TowerDefense::Smithing::Render()
{
	Player& player = Player::Get();
	player.RenderDeck();

	std::shared_ptr<HeroCard> heroCard = std::dynamic_pointer_cast<HeroCard>(m_SelectedCard);
	if (m_SelectedCard && heroCard)
	{
		m_Fade->Render();
		if (!player.GetSelectedDeckCard())
			m_Cancel->Render();
		if (heroCard->GetUpgrades()->GetSelectedCard())
			m_Confirm->Render();
		heroCard->GetUpgrades()->Render();
	}
	else if (m_SelectedCard && !m_SelectedCard->IsUpgraded())
	{
		m_Fade->Render();
		if (!player.GetSelectedDeckCard())
			m_Cancel->Render();
		m_SelectedCardImage->Render();
		m_SelectedCard->RenderUpgrade(500, 300);
		m_SmithingArrow->Render();
		m_Confirm->Render();
	}
	else if (!player.GetSelectedDeckCard())
	{
		m_Cancel->Render();
	}
}

void TowerDefense::Smithing::Update()
{
	Player& player = Player::Get();
	std::shared_ptr<HeroCard> heroCard = std::dynamic_pointer_cast<HeroCard>(m_SelectedCard);
	if (m_SelectedCard && heroCard)
	{
		bool showingInfo = heroCard->GetUpgrades() && heroCard->GetUpgrades()->ShowingInfo();

		if (heroCard->GetUpgrades()->GetSelectedCard() && !showingInfo)
		{
			m_Confirm->Update();
			if (m_Confirm->IsClicked())
			{
				m_ActivityDone = true;
				m_Exit = true;
				player.ShowDeck(false);
				heroCard->Upgrade();
			}
		}

		if (!player.GetSelectedDeckCard() && !showingInfo)
		{
			m_Cancel->Update();
			if (m_Cancel->IsClicked())
				m_SelectedCard.reset();
		}

		if (heroCard->GetUpgrades())
			heroCard->GetUpgrades()->Update();
	}
	else if (m_SelectedCard && !m_SelectedCard->IsUpgraded())
	{
		m_Confirm->Update();
		if (m_Confirm->IsClicked())
		{
			m_ActivityDone = true;
			m_Exit = true;
			player.ShowDeck(false);
			m_SelectedCard->Upgrade();
		}
		if (!player.GetSelectedDeckCard())
		{
			m_Cancel->Update();
			if (m_Cancel->IsClicked())
				m_SelectedCard.reset();
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

	if (!m_SelectedCard || m_SelectedCard->IsUpgraded())
	{
		if (!player.GetSelectedDeckCard())
			FindSelectedCard();
		if (!m_SelectedCard)
			player.UpdateDeck();
	}
}

void TowerDefense::Smithing::OnSwitch()
{
	BaseScene::OnSwitch();
	Player::Get().ShowDeck(true);
	m_SelectedCard.reset();
}

void TowerDefense::Smithing::FindSelectedCard()
{
	if (!Input::GetLeftMouseClicked())
		return;

	m_SelectedCard = Player::Get().GetClickedDeckCard();
	if (m_SelectedCard)
	{
		m_SelectedCardImage = m_SelectedCard->Clone();
		m_SelectedCardImage->SetX(300);
		m_SelectedCardImage->SetY(300);
	}
}