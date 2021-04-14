#include "pch.h"
#include "Explorer.h"
#include "core/Player.h"

TowerDefense::Quirk::Explorer::Explorer()
	:Quirk("Explorer")
{

}

void TowerDefense::Quirk::Explorer::OnPlay()
{
	Player::Get().GetHand()->DrawCard();
}

std::string TowerDefense::Quirk::Explorer::GetNameText(Gender gender) const
{
	return "adventurous";
}

std::shared_ptr<TowerDefense::Quirk::Quirk> TowerDefense::Quirk::Explorer::Clone()
{
	return std::make_shared<Explorer>();
}