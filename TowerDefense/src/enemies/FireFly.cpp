#include "pch.h"
#include "Enemies.h"
#include "core/Player.h"
#include "cards/curses/Curses.h"

void TowerDefense::Enemy::FireFly::Destroy()
{
	Enemy::Destroy();

	if (m_Health > 0)
		return;

	Player::Get().AddToDrawPile(std::make_shared<Flames>());
}