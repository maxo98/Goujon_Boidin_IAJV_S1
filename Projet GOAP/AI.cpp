#include "AI.h"
#include <iostream>

#include "Action.h"

void AI::Plan(Action* action)
{
	/*for (unsigned int i = 0; i < action->PreconditionsCount(); i++)
	{
		if (!action->GetPrecondition(i)->IsTrue())
		{
			
		}
	}*/
}

std::vector<Action*> AI::ReverseAStar(Action* action)
{
	std::vector<Action*> exit;

	std::vector<std::pair<Action*, int>> frontier;
	frontier.push_back(std::pair<Action*, int>(action, 0));

	std::map<Action*, Action*> cameFrom;
	std::map<Action*, int> costSoFar;

	costSoFar[action] = action->GetCost();
	cameFrom[action] = nullptr;

	while (!frontier.empty())
	{
		Action* currentAction = frontier.back().first;
		frontier.pop_back();

		int currentCost = costSoFar[currentAction];
		bool endBranch = true;

		for (unsigned int i = 0; i < action->PreconditionsCount(); i++)
		{
			if (!action->GetPrecondition(i)->IsTrue())
			{
				endBranch = false;

				std::vector<Action*> actionsToDo = availableActions[action->GetPrecondition(i)];

				for (int i = 0; i < actionsToDo.size(); i++)
				{
					
					if (cameFrom.find(actionsToDo[i]) != cameFrom.end() || (currentCost + actionsToDo[i]->GetCost() + 1) <= costSoFar[actionsToDo[i]])
					{
						frontier.push_back(std::pair<Action*, int>(actionsToDo[i], currentCost + actionsToDo[i]->GetCost() + 1));
						cameFrom[actionsToDo[i]] = currentAction;
					}
				}
			}
		}

		if (endBranch == true)
		{
			exit.push_back(currentAction);

			if (cameFrom[currentAction] != action)
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
}





