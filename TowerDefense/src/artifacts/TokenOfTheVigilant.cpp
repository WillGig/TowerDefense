#include "pch.h"
#include "Artifact.h"
#include "core/Player.h"

TowerDefense::TokenOfTheVigilant::TokenOfTheVigilant()
	:Artifact("TokenOfTheVigilant"), m_Counter(0)
{
}

void TowerDefense::TokenOfTheVigilant::OnCardPlay(std::shared_ptr<Card> c)
{
	if (c->GetCardType() == CardType::SKILL)
	{
		m_Counter++;
		if (m_Counter == 2)
		{
			Player::Get().ChangeEnergy(10);
			m_Counter = 0;
		}
	}
}