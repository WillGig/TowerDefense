#include "pch.h"
#include "Artifact.h"
#include "enemies/Enemy.h"

TowerDefense::MiniatureWormHole::MiniatureWormHole()
	:Artifact("Miniature Worm Hole"), m_Ready(true)
{}

void TowerDefense::MiniatureWormHole::OnFightStart()
{
	m_Ready = true;
}

void TowerDefense::MiniatureWormHole::OnEnemyReachedEnd(std::shared_ptr<Enemy::Enemy> e)
{
	if (m_Ready)
	{
		e->SetDistanceTravelled(0);
		m_Ready = false;
	}
}