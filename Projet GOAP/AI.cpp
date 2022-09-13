#include "AI.h"
#include <iostream>

#include "Action.h"

AI::~AI()
{
	std::map<Precondition::Types, std::vector<Action*>>::iterator itMap;
	for(itMap = availableActions.begin(); itMap != availableActions.end(); ++itMap)
	{
		while(itMap->second.size() > 0)
		{
			delete itMap->second[itMap->second.size() - 1];
			itMap->second.pop_back();
		}
	}

	availableActions.clear();
}

void AI::Plan(Action* action)
{
	bool isPossible = true;
	std::list<Action*> actionList;

	actionList.push_front(action);

	for (unsigned int i = 0; i < action->PreconditionsCount(); i++)
	{
		if (!action->GetPrecondition(i)->IsTrue(this))
		{
			std::pair<std::list<Action*>, int> newPath = ReverseAStar(action->GetPrecondition(i)->GetType());

			if (newPath.second != -1)
			{
				actionList.splice(actionList.begin(), newPath.first);
			}
			else {
				isPossible = false;
			}
		}
	}

	for (std::list<Action*>::iterator it = actionList.begin(); it != actionList.end(); ++it)
	{
		(*it)->Execute(this);
	}
}

std::pair<std::list<Action*>, int> AI::ReverseAStar(Precondition::Types precondition)
{
	//Needs to be a list so pointers don't change
	std::list < std::pair<std::list<Action*>, int> > computedPaths;
	std::pair<std::list<Action*>, int>* pBestPath = nullptr;

	std::vector<Action*> actionsToTest = availableActions[precondition];

	//For each action that can potentially solves the precondition, compute paths
	for (int i = 0; i < actionsToTest.size(); i++)
	{
		if (pBestPath != nullptr && actionsToTest[i]->GetCost(this) >= pBestPath->second)
			continue;

		computedPaths.push_back(std::pair<std::list<Action*>, int>(std::list<Action*>(), actionsToTest[i]->GetCost(this)));
		computedPaths.back().first.push_back(actionsToTest[i]);

		//For each precondition not filled enter compute best path to fill it and append it to the path
		for (unsigned int i = 0; i < actionsToTest[i]->PreconditionsCount(); i++)
		{
			if (!actionsToTest[i]->GetPrecondition(i)->IsTrue(this))
			{
				std::pair<std::list<Action*>, int> newPath = ReverseAStar(actionsToTest[i]->GetPrecondition(i)->GetType());

				if (newPath.second != -1)
				{
					computedPaths.back().first.splice(computedPaths.back().first.begin(), newPath.first);
					computedPaths.back().second += newPath.second;
				}
				else {
					computedPaths.back().second = -1;
				}
			}
		}

		if ((pBestPath == nullptr && computedPaths.back().second != -1) || (pBestPath != nullptr && computedPaths.back().second < pBestPath->second))
		{
			pBestPath = &computedPaths.back();
		}
	}

	if (pBestPath == nullptr)
	{
		return std::pair<std::list<Action*>, int>(std::list<Action*>(), -1);
	}

	return *pBestPath;
}

