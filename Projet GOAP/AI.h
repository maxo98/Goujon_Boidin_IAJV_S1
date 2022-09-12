#pragma once
#include <vector>
#include "Precondition.h"
#include "Action.h"
#include <map>
#include <queue>

class AI
{
private:
	std::map<Precondition*,std::vector<Action*>> availableActions;

public:
	void Plan(Action* action);

	void ReverseAStar(Action* action);

	std::vector<Action*> GetActionsFromPrecondition(Precondition* precondition)
	{
		return availableActions[precondition];
	}
};




