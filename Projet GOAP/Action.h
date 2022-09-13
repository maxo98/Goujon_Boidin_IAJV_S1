#pragma once
#include <vector>
#include "Effect.h"
#include "Precondition.h"
#include "AI.h"
#include <iostream>

class Action
{
protected:
	std::vector<Precondition*> preconditions;
	std::vector<Effect*> effects;
	int cost;

public:

	~Action();

	void Execute(AI* actor);

	unsigned int EffectsCount() { effects.size(); }

	unsigned int PreconditionsCount() { return preconditions.size(); }

	Effect* GetEffect(int i) { return effects[i]; }

	Precondition* GetPrecondition(int i) { return preconditions[i]; }

	virtual int GetCost(AI* actor) { return cost; }
};

class AttackPlayerAction: public Action
{
public:
	AttackPlayerAction();
};

class BuyWeaponAction : public Action
{
public:
	BuyWeaponAction();
};

class ReloadAction : public Action
{
public:
	ReloadAction();
};

class MoveToPlayerAction : public Action
{
public:
	MoveToPlayerAction();

	virtual int GetCost(AI* actor);
};

class StealWeaponAction : public Action
{
public:
	StealWeaponAction();
};

class StealPotionAction : public Action
{
public:
	StealPotionAction();
};

class WorkAction : public Action
{
public:
	WorkAction();
};

class StudyAction : public Action
{
public:
	StudyAction();
};

class BuyPotionAction : public Action
{
public:
	BuyPotionAction();
};

class DrinkPotionAction : public Action
{
public:
	DrinkPotionAction();
};
