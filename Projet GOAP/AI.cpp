#include "AI.h"

void AI::Plan(Action* action)
{
	/*for (unsigned int i = 0; i < action->PreconditionsCount(); i++)
	{
		if (!action->GetPrecondition(i)->IsTrue())
		{
			
		}
	}*/
}

void AI::ReverseAStar(Action* action)
{
	std::priority_queue<Action*, int> frontier;
	frontier.push(action);

	std::map<Action*, Action*> cameFrom;
	std::map<Action*, int> costSoFar;

	while (!frontier.empty())
	{
		Action* currentAction = frontier.top();
		frontier.pop();

		for (unsigned int i = 0; i < action->PreconditionsCount(); i++)
		{
			if (!action->GetPrecondition(i)->IsTrue())
			{
				std::vector<Action*> actionsToDo = availableActions[action->GetPrecondition(i)];

			}
		}
	}
}





