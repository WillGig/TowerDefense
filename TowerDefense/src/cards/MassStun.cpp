#include "pch.h"
#include "SkillCards.h"
#include "scenes/Combat.h"

TowerDefense::MassStun::MassStun()
	:Card("Mass Stun", CardType::SKILL, 30, "massStun", "massStunUpgraded")
{
}

bool TowerDefense::MassStun::Play()
{
	int stunDuration = m_Upgraded ? 300 : 180;

	auto entities = Combat::GetEntities();
	for (unsigned int i = 0; i < entities->size(); i++) {
		std::shared_ptr<Entity> e = entities->at(i);
		if (e->GetEntityType() == Type::ENEMY)
			std::dynamic_pointer_cast<Enemy::Enemy>(e)->Stun(stunDuration);
	}

	return true;
}

std::shared_ptr<TowerDefense::Card> TowerDefense::MassStun::Clone()
{
	auto card = std::make_shared<MassStun>();
	if (m_Upgraded)
		card->Upgrade();
	return card;
}