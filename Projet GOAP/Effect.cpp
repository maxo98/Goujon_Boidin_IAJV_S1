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

	casted->SetMoney(false);
	casted->SetWeapon(1);
	casted->SetAmmo(5);

	std::cout << "Actor buys a weapon" << std::endl;
}

void MoveToPlayerEffect::ApplyEffect(AI* actor)
{
	Actor* casted = (Actor*)actor;
	assert(casted != nullptr);

	casted->SetPlayerDistance(0);

	std::cout << "Actor moves in range to player" << std::endl;
}

void GetMoneyEffect::ApplyEffect(AI* actor)
{
	Actor* casted = (Actor*)actor;
	assert(casted != nullptr);

	casted->SetMoney(true);

	std::cout << "Actor works to get money" << std::endl;
}

void GetDegreeEffect::ApplyEffect(AI* actor)
{
	Actor* casted = (Actor*)actor;
	assert(casted != nullptr);

	casted->SetDegree(true);

	std::cout << "Actor works to gets a degree" << std::endl;
}

void GetHealthPotionEffect::ApplyEffect(AI* actor)
{
	Actor* casted = (Actor*)actor;
	assert(casted != nullptr);

	casted->SetMoney(false);
	casted->SetHealthPotion(casted->GetHealthPotion() + 1);

	std::cout << "Actor buys an health potion" << std::endl;
}

void GetHealthEffect::ApplyEffect(AI* actor)
{
	Actor* casted = (Actor*)actor;
	assert(casted != nullptr);

	casted->SetLowHealth(false);

	std::cout << "Actor drinks an health potion" << std::endl;
}

void StealWeaponEffect::ApplyEffect(AI* actor)
{
	Actor* casted = (Actor*)actor;
	assert(casted != nullptr);

	casted->SetWeapon(1);

	std::cout << "Actor steals an weapon" << std::endl;
}

void StealPotionEffect::ApplyEffect(AI* actor)
{
	Actor* casted = (Actor*)actor;
	assert(casted != nullptr);

	casted->SetHealthPotion(casted->GetHealthPotion() + 1);

	std::cout << "Actor steals an health potion" << std::endl;
}