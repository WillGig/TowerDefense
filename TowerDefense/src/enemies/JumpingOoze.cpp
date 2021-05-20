#include "pch.h"
#include "Enemies.h"
#include "core/Board.h"

//Move normally when jump is on cooldown
//When able to jump, move in an arc to m_JumpGoal
//Jump should be completed in m_JumpTime
void TowerDefense::Enemy::JumpingOoze::Move()
{
	//Check if ready to Jump and move to next frame if jumping
	if (m_JumpCoolDown != 0)
		m_JumpCoolDown--;

	if (m_JumpCoolDown == 0)
	{
		if (m_JumpFrame == 0)
		{
			SetX(m_JumpGoal.x);
			SetY(m_JumpGoal.y);
			m_JumpFrame = m_JumpTime + 1;
			m_JumpCoolDown = m_TimeBetweenJumps;
		}
		else
			m_JumpFrame--;
	}
		
	//If jump is on cooldown, move normally
	if (m_JumpCoolDown != 0)
	{
		Enemy::Move();
		return;
	}

	//Find jump destination and start
	if (m_JumpFrame == m_JumpTime)
	{
		m_JumpGoal = FindJumpDestination();
		m_JumpStart = Vec2(m_X, m_Y);
	}
		
	//Ooze moves up and down through jump
	m_Y += (int)(10 * ((float)(m_JumpFrame - (m_JumpTime / 2)) / (float)m_JumpTime));

	//Ooze moves towards the end of jump
	SetX(m_X + (m_JumpGoal.x - m_JumpStart.x) / (float)m_JumpTime);
	SetY(m_Y + (m_JumpGoal.y - m_JumpStart.y) / (float)m_JumpTime);
		
}

//Find point along the path that is m_JumpDistance away where the enemy will land
Vec2 TowerDefense::Enemy::JumpingOoze::FindJumpDestination()
{
	Vec2 currentPosition(m_X, m_Y);

	float distanceToTravel = (float)m_JumpDistance;
	float distanceToGoal = (float)sqrt(pow(currentPosition.x - m_GoalX, 2) + pow(currentPosition.y - m_GoalY, 2.0));

	distanceToTravel -= distanceToGoal;
	while (true)
	{
		currentPosition = Vec2(m_GoalX, m_GoalY);
		FindNewGoal(currentPosition.x, currentPosition.y);

		if (m_ReachedEnd)
		{
			m_ReachedEnd = false;
			return currentPosition;
		}

		distanceToGoal = (float)sqrt(pow(currentPosition.x - m_GoalX, 2) + pow(currentPosition.y - m_GoalY, 2.0));

		if (distanceToGoal < distanceToTravel)
			distanceToTravel -= distanceToGoal;
		else
			break;
	}
	
	if (currentPosition.x < m_GoalX)
		currentPosition.x += distanceToTravel;
	else if (currentPosition.x > m_GoalX)
		currentPosition.x -= distanceToTravel;
	else if (currentPosition.y < m_GoalY)
		currentPosition.y += distanceToTravel;
	else if (currentPosition.y > m_GoalY)
		currentPosition.y -= distanceToTravel;

	return currentPosition;
}