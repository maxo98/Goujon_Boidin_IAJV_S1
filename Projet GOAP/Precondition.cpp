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

bool HasHealthPotion::IsTrue(AI* actor)
{
	Actor* casted = (Actor*)(actor);

	assert(casted != nullptr);

	return (casted->GetHealthPotion() > 0);
}

bool HasMoney::IsTrue(AI* actor)
{
	Actor* casted = (Actor*)(actor);

	assert(casted != nullptr);

	return casted->HasMoney();
}

bool HasDegree::IsTrue(AI* actor)
{
	Actor* casted = (Actor*)(actor);

	assert(casted != nullptr);

	return casted->HasDegree();
}

bool IsHealthy::IsTrue(AI* actor)
{
	Actor* casted = (Actor*)(actor);

	assert(casted != nullptr);

	return !casted->IsLowHealth();
}