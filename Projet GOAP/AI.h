#pragma once
#include <vector>
#include "Precondition.h"

#include <map>
#include <queue>
#include <list>

class Action;

inline bool sort(std::pair<Action*, int> i, std::pair<Action*, int> j) { return (i.second < j.second); }

class AI
{
private:
	std::map<Precondition*,std::vector<Action*>> availableActions;

public:
	void Plan(Action* action);

	std::pair<std::list<Action*>, int> ReverseAStar(Precondition* precondition);

	std::vector<Action*> GetActionsFromPrecondition(Precondition* precondition)
	{
		return availableActions[precondition];
	}
};



