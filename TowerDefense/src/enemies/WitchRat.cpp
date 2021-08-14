#include "pch.h"
#include "Enemies.h"
#include "scenes/Combat.h"
#include "core/Player.h"
#include "cards/curses/Curses.h"

void TowerDefense::Enemy::WitchRat::Update()
{
	Enemy::Update();

	for (int i = 0; i < Combat::GetRoundSpeed(); i++)
	{
		if (m_Cast == m_CastTime)
		{
			Player::Get().AddToDrawPile(std::make_shared<Hex>());
			//TODO: play animation
			m_Cast = 0;
		}
		else
			m_Cast++;
	}
}