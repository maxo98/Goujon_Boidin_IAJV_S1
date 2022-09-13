#pragma once
#include <vector>
#include "Effect.h"
#include "Precondition.h"
#include "AI.h"

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

class GetWeaponAction : public Action
{
public:
	GetWeaponAction();
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