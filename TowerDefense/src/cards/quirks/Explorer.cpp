#include "pch.h"
#include "quirk.h"
#include "core/Player.h"

TowerDefense::Quirk::Explorer::Explorer()
	:Quirk("Explorer")
{

}

void TowerDefense::Quirk::Explorer::OnPlay()
{
	Player::Get().GetHand()->DrawCard();
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Explorer::Clone()
{
	return std::make_shared<Explorer>();
}