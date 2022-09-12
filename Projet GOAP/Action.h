#pragma once
#include <vector>
#include "Effect.h"
#include "Precondition.h"

class Action
{
private:
	std::vector<Precondition*> preconditions;
	std::vector<Effect*> effects;
	int cost;

public:

	void Execute(AI& actor);

	unsigned int EffectsCount() { effects.size(); }

	unsigned int PreconditionsCount() { preconditions.size(); }

	Effect* GetEffect(int i) { return effects[i]; }

	Precondition* GetPrecondition(int i) { return preconditions[i]; }

	int GetCost() { return cost; }

	
};

