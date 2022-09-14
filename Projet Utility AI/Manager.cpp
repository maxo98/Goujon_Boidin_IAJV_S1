#include <windows.h>
#include <iostream>
#include <string>
#include "Manager.h"
#include "World.h"
#include "Action.h"
#include "WorldSettings.h"



Manager* Manager::managerSingleton = nullptr;

Manager::Manager()
{
	InitManager();
}

Manager* Manager::GetInstance()
{
	if (managerSingleton == nullptr)
		managerSingleton = new Manager();
	return managerSingleton;
}

void Manager::InitManager()
{
	availableActions.reserve((int) ACTION_TYPE::LENGTH);

	//ajouter tout les types d'action
	availableActions.push_back(new CreateVillager());
	availableActions.push_back(new ProduceFood());


	world = new World();
}

void Manager::DeInit()
{
	for (Action* action : availableActions)
	{
		if(action != nullptr)
		{
			action->DeInit();
			delete action;
			action = nullptr;
		}
	}

}

void Manager::Update()
{
	std::cout << "Food : " << std::to_string(world->GetRessourceAmount((RESSOURCE_TYPE)0)) << std::endl;
	int selectedAction = EvaluateActions();
	if(selectedAction != -1)
		availableActions[selectedAction]->ExecuteAction(world);

}

int Manager::EvaluateActions()
{
	int selectedAction = -1;
	float actionValue = 0;
	for (int i = 0; i < availableActions.size(); i++)
	{
		if (!availableActions[i]->CanDoAction(world))
			continue;

		float currentActionValue = availableActions[i]->EvaluateAction(world);
		if (currentActionValue > actionValue)
		{
			actionValue = currentActionValue;
			selectedAction = i;
		}
	}
	return selectedAction;
}
