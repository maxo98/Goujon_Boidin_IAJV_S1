#include <iostream>
#include <assert.h>
#include "Action.h"
#include "AI.h"
#include "Actor.h"

void Action::Execute(AI* actor)
{
	for (unsigned int i = 0; i < preconditions.size(); i++)
	{
		assert(!preconditions[i]->IsTrue(actor));
	}

	for (unsigned int i = 0; i < effects.size(); i++)
	{
		effects[i]->ApplyEffect(actor);
	}
}

Action::~Action()
{
	while (preconditions.size() > 0)
	{
		delete preconditions[preconditions.size() - 1];
		preconditions.pop_back();
	}

	while (effects.size() > 0)
	{
		delete effects[effects.size() - 1];
		effects.pop_back();
	}
}

AttackPlayerAction::AttackPlayerAction()
{
	cost = 2;

	preconditions.push_back(new HasAmmo());
	preconditions.push_back(new HasWeapon());
	preconditions.push_back(new PlayerInRange());

	effects.push_back((Effect*)new AttackPlayer());
}

GetWeaponAction::GetWeaponAction()
{
	effects.push_back((Effect*)new GetWeaponEffect());

	cost = 3;
}

ReloadAction::ReloadAction()
{
	effects.push_back((Effect*)new ReloadEffect());

	cost = 1;
}

MoveToPlayerAction::MoveToPlayerAction()
{
	effects.push_back((Effect*)new MoveToPlayerEffect());
}

int MoveToPlayerAction::GetCost(AI* actor)
{
	Actor* casted = (Actor*)(actor);

	assert(casted != nullptr);

	return casted->GetPlayerDistance();
}