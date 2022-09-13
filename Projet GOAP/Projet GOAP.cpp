#include <iostream>
#include "Actor.h"
#include "Action.h"
#include "Precondition.h"

int main()
{

	Actor actor;

	Action* action = new AttackPlayerAction();

	actor.Plan(action);

	delete action;
}