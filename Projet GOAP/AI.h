#pragma once
#include <vector>
#include "Precondition.h"

#include <map>
#include <list>

class Action;

class AI
{
protected:
	std::map<Precondition::Types,std::vector<Action*>> availableActions;

public:
	~AI();

	void Plan(Action* action);

	std::pair<std::list<Action*>, int> ReverseAStar(Precondition::Types precondition);

	std::vector<Action*> GetActionsFromPrecondition(Precondition::Types precondition)
	{
		return availableActions[precondition];
	}
};



