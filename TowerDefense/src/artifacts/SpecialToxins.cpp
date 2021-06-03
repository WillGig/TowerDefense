#include "pch.h"
#include "Artifact.h"
#include "towers/Tower.h"
#include "enemies/Enemy.h"

TowerDefense::SpecialToxins::SpecialToxins()
	:Artifact("Special Toxins")
{}

void TowerDefense::SpecialToxins::OnEnemyHit(std::shared_ptr<Enemy::Enemy> e, std::shared_ptr<Entity> source, Tower::DamageType type)
{
	if (type == Tower::DamageType::POISON)
		e->TakeDamage(1.0f, GetID(), Tower::DamageType::TRUE);
}
