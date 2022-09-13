#include <iostream>
#include <assert.h>
#include "Action.h"
#include "AI.h"

void Action::Execute(AI* actor)
{
	for (unsigned int i = 0; i < preconditions.size(); i++)
	{
		assert(!preconditions[i]->IsTrue());
	}

	for (unsigned int i = 0; i < effects.size(); i++)
	{
		effects[i]->ApplyEffect(actor);
	}
}
