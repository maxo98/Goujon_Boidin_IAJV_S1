#include "Effect.h"
#include <iostream>
#include "Actor.h"
#include <cassert>

void AttackPlayer::ApplyEffect(AI* actor)
{
	Actor* casted = (Actor*)actor;
	assert(casted != nullptr);

	casted->SetAmmo(casted->GetAmmo()-1);

	std::cout << "Actor attacks player" << std::endl;
}

void ReloadEffect::ApplyEffect(AI* actor)
{
	Actor* casted = (Actor*)actor;
	assert(casted != nullptr);

	casted->SetAmmo(5);

	std::cout << "Actor reloads" << std::endl;
}

void GetWeaponEffect::ApplyEffect(AI* actor)
{
	Actor* casted = (Actor*)actor;
	assert(casted != nullptr);

	casted->SetWeapon(1);

	std::cout << "Actor gets weapon" << std::endl;
}

void MoveToPlayerEffect::ApplyEffect(AI* actor)
{
	Actor* casted = (Actor*)actor;
	assert(casted != nullptr);

	casted->SetPlayerDistance(0);

	std::cout << "Actor moves in range to player" << std::endl;
}