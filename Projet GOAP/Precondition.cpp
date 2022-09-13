#include "Precondition.h"
#include "Actor.h"
#include "AI.h"
#include <iostream>
#include <assert.h>

bool HasAmmo::IsTrue(AI* actor)
{
	Actor* casted = (Actor*)(actor);
	
	assert(casted != nullptr);

	return (casted->GetAmmo() > 0);
}

bool HasWeapon::IsTrue(AI* actor)
{
	Actor* casted = (Actor*)(actor);

	assert(casted != nullptr);

	return (casted->GetWeapon() > 0);
}

bool PlayerInRange::IsTrue(AI* actor)
{
	Actor* casted = (Actor*)(actor);

	assert(casted != nullptr);

	return (casted->GetPlayerDistance() == 0);
}