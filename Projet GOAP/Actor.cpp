#include "Actor.h"
#include "Action.h"

Actor::Actor()
{
	availableActions[Precondition::Types::HasWeapon] = std::vector<Action*>();
	availableActions[Precondition::Types::HasWeapon].push_back((Action*)new BuyWeaponAction());
	availableActions[Precondition::Types::HasWeapon].push_back((Action*)new StealWeaponAction());

	availableActions[Precondition::Types::HasAmmo] = std::vector<Action*>();
	availableActions[Precondition::Types::HasAmmo].push_back((Action*)new StealWeaponAction());
	availableActions[Precondition::Types::HasAmmo].push_back((Action*)new BuyWeaponAction());
	availableActions[Precondition::Types::HasAmmo].push_back((Action*)new ReloadAction());

	availableActions[Precondition::Types::PlayerInRange] = std::vector<Action*>();
	availableActions[Precondition::Types::PlayerInRange].push_back((Action*)new MoveToPlayerAction());

	availableActions[Precondition::Types::HasMoney] = std::vector<Action*>();
	availableActions[Precondition::Types::HasMoney].push_back((Action*)new WorkAction());

	availableActions[Precondition::Types::HasDegree] = std::vector<Action*>();
	availableActions[Precondition::Types::HasDegree].push_back((Action*)new StudyAction());

	availableActions[Precondition::Types::HasHealthPotion] = std::vector<Action*>();
	availableActions[Precondition::Types::HasHealthPotion].push_back((Action*)new BuyPotionAction());
	availableActions[Precondition::Types::HasHealthPotion].push_back((Action*)new StealPotionAction());

	availableActions[Precondition::Types::IsHealthy] = std::vector<Action*>();
	availableActions[Precondition::Types::IsHealthy].push_back((Action*)new DrinkPotionAction());
}