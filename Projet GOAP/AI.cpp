#include "AI.h"
#include <iostream>

#include "Action.h"

void AI::Plan(Action* action)
{
	bool isPossible = true;
	std::list<Action*> actionList;

	actionList.push_front(action);

	for (unsigned int i = 0; i < action->PreconditionsCount(); i++)
	{
		if (!action->GetPrecondition(i)->IsTrue())
		{
			std::pair<std::list<Action*>, int> newPath = ReverseAStar(action->GetPrecondition(i));

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

std::pair<std::list<Action*>, int> AI::ReverseAStar(Precondition* precondition)
{
	std::vector < std::pair<std::list<Action*>, int> > computedPaths;
	std::pair<std::list<Action*>, int>* pBestPath = nullptr;
	int n = 0;

	std::vector<Action*> actionsToTest = availableActions[precondition];

	//For each action that can potentially solves the precondition, compute paths
	for (int i = 0; i < actionsToTest.size(); i++)
	{
		if (pBestPath != nullptr && actionsToTest[i]->GetCost() >= pBestPath->second)
			continue;

		computedPaths.push_back(std::pair<std::list<Action*>, int>(std::list<Action*>(), actionsToTest[i]->GetCost()));
		computedPaths[n].first.push_back(actionsToTest[i]);

		//For each precondition not filled enter compute best path to fill it and append it to the path
		for (unsigned int i = 0; i < actionsToTest[i]->PreconditionsCount(); i++)
		{
			if (!actionsToTest[i]->GetPrecondition(i)->IsTrue())
			{
				std::pair<std::list<Action*>, int> newPath = ReverseAStar(actionsToTest[i]->GetPrecondition(i));

				if (newPath.second != -1)
				{
					computedPaths[n].first.splice(computedPaths[n].first.begin(), newPath.first);
					computedPaths[n].second += newPath.second;
				}
				else {
					computedPaths[n].second = -1;
				}
			}
		}

		if ((pBestPath == nullptr && computedPaths[n].second != -1) || (pBestPath != nullptr && computedPaths[n].second < pBestPath->second))
		{
			pBestPath = &computedPaths[n];
		}
		n++;
	}

	if (pBestPath == nullptr)
	{
		return std::pair<std::list<Action*>, int>(std::list<Action*>(), -1);
	}

	return *pBestPath;
}

/*
std::vector<Action*> AI::ReverseAStar(Precondition* precondition)
{
	std::vector<Action*> exit;

	std::vector<std::pair<Action*, int>> frontier;

	std::map<Action*, Action*> cameFrom;
	std::map<Action*, int> costSoFar;

	std::vector<Action*> actionsToAdd = availableActions[precondition];

	for (int i = 0; i < actionsToAdd.size(); i++)
	{
		frontier.push_back(std::pair<Action*, int>(actionsToAdd[i], actionsToAdd[i]->GetCost() + 1));
		cameFrom[actionsToAdd[i]] = nullptr;
	}

	while (!frontier.empty())
	{
		Action* currentAction = frontier.back().first;
		frontier.pop_back();

		int currentCost = costSoFar[currentAction];
		bool endBranch = true;

		for (unsigned int i = 0; i < currentAction->PreconditionsCount(); i++)
		{
			if (!currentAction->GetPrecondition(i)->IsTrue())
			{
				endBranch = false;

				std::vector<Action*> actionsToAdd = availableActions[currentAction->GetPrecondition(i)];

				if (actionsToAdd.size() > 1)
				{

					std::vector<Action*> pathToAppend = ReverseAStar(currentAction->GetPrecondition(i));
					int newCost = currentCost;


					for (int i = pathToAppend.size() - 1; i > -1; i--)
					{
						newCost += pathToAppend[i]->GetCost() + 1;

						frontier.push_back(std::pair<Action*, int>(actionsToAdd[0], newCost));
						cameFrom[actionsToAdd[0]] = currentAction;
						costSoFar[actionsToAdd[0]] = newCost;
					}
				}
				else {
					int newCost = currentCost + actionsToAdd[0]->GetCost() + 1;

					frontier.push_back(std::pair<Action*, int>(actionsToAdd[0], newCost));
					cameFrom[actionsToAdd[0]] = currentAction;
					costSoFar[actionsToAdd[0]] = newCost;
				}
			}
		}

		if (endBranch == true)
		{
			exit.push_back(currentAction);

			if (cameFrom[currentAction] != nullptr)
			{
				break;
			}
		}

		std::sort(frontier.begin(), frontier.end(), sort);
	}

	if (exit.size() == 0)
	{
		std::cout << "Can't find a soltuion." << std::endl;
	}

	Action* bestExit = exit[0];
	int bestExitCost = costSoFar[exit[0]];

	for (int i = 1; i < exit.size(); i++)
	{
		if (costSoFar[exit[i]] < bestExitCost)
		{
			bestExit = exit[i];
			bestExitCost = costSoFar[exit[i]];
		}
	}

	std::vector<Action*> solution;

	solution.push_back(bestExit);

	while (cameFrom[solution.back()] != nullptr)
	{
		solution.push_back(cameFrom[solution.back()]);
	}

	return solution;
}*/





