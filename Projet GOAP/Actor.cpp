#include "Actor.h"
#include "Action.h"

Actor::Actor()
{
	availableActions[Precondition::Types::HasWeapon] = std::vector<Action*>();
	availableActions[Precondition::Types::HasWeapon].push_back((Action*)new GetWeaponAction());

	availableActions[Precondition::Types::HasAmmo] = std::vector<Action*>();
	availableActions[Precondition::Types::HasAmmo].push_back((Action*)new GetWeaponAction());
	availableActions[Precondition::Types::HasAmmo].push_back((Action*)new ReloadAction());

	availableActions[Precondition::Types::PlayerInRange] = std::vector<Action*>();
	availableActions[Precondition::Types::PlayerInRange].push_back((Action*)new MoveToPlayerAction());
}