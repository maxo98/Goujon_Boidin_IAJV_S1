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
	world = new World();

	std::vector<Action*> actionForVillager;
	actionForVillager.reserve((int)ACTION_TYPE::LENGTH - (int)ACTION_TYPE::LENGTHCREATE);

	//add actions in a vector for each type of actor
	actionForVillager.push_back(new GatherWater(world));
	actionForVillager.push_back(new BuildHouse(world));
	availableActionsForActors.emplace(ACTOR_TYPE::VILLAGER, actionForVillager);

	std::vector<Action*> actionForLumberjack;
	actionForLumberjack.reserve((int)ACTION_TYPE::LENGTH - (int)ACTION_TYPE::LENGTHCREATE);
	actionForLumberjack.push_back(new ChopWood(world));
	availableActionsForActors.emplace(ACTOR_TYPE::LUMBERJACK, actionForLumberjack);

	std::vector<Action*> actionForFarmer;
	actionForFarmer.reserve((int)ACTION_TYPE::LENGTH - (int)ACTION_TYPE::LENGTHCREATE);
	actionForFarmer.push_back(new ProduceFood(world));
	availableActionsForActors.emplace(ACTOR_TYPE::FARMER, actionForFarmer);

	availableActionsCreateActors.reserve((int) ACTION_TYPE::LENGTHCREATE);
	availableActionsCreateActors.push_back(new CreateVillager(world));
	availableActionsCreateActors.push_back(new CreateFarmer(world));
	availableActionsCreateActors.push_back(new CreateLumberjack(world));

	
}

void Manager::DeInit()
{
	for (int i = 0; i < (int)ACTOR_TYPE::LENGTH; i++)
	{
		for(int j = (int) ACTION_TYPE::LENGTHCREATE; j < (int) ACTION_TYPE::LENGTH - (int)ACTION_TYPE::LENGTHCREATE; j++)
		{
			if (availableActionsForActors[(ACTOR_TYPE)i][j] != nullptr)
			{
				availableActionsForActors[(ACTOR_TYPE)i][j]->DeInit();
				delete availableActionsForActors[(ACTOR_TYPE)i][j];
				availableActionsForActors[(ACTOR_TYPE)i][j] = nullptr;
			}
		}
	}
	for (Action* action : availableActionsCreateActors)
	{
		if (action != nullptr)
		{
			action->DeInit();
			delete action;
			action = nullptr;
		}
	}
}

void Manager::Update()
{
	resetActions();
	ShowStats();
	int selectedAction = 0;
	for (int i = 0; i < (int)ACTOR_TYPE::LENGTH; i++)
	{
		for (Actor* actor : world->GetActorsFromType((ACTOR_TYPE)i))
		{
			selectedAction = EvaluateActions(&availableActionsForActors[(ACTOR_TYPE)i]);
			if (selectedAction > -1)
			{
				availableActionsForActors[(ACTOR_TYPE)i][selectedAction]->ExecuteAction(world);
			}
		}
	}
	selectedAction = EvaluateActions(&availableActionsCreateActors);
	if (selectedAction != -1)
		availableActionsCreateActors[selectedAction]->ExecuteAction(world);
	world->WorldUpdate();
}

int Manager::EvaluateActions(std::vector<Action*>* actions)
{
	int selectedAction = -1;
	float actionValue = 0;
	for (unsigned int i = 0; i < actions->size(); i++)
	{
		if (!(*actions)[i]->CanDoAction(world))
			continue;

		float currentActionValue =(*actions)[i]->EvaluateAction(world);
		if (currentActionValue > actionValue)
		{
			actionValue = currentActionValue;
			selectedAction = i;
		}
	}
	return selectedAction;
}

void Manager::resetActions()
{
	for (int i = 0; i < (int)ACTOR_TYPE::LENGTH; i++)
	{
		for (Action* action : availableActionsForActors[(ACTOR_TYPE)i])
		{
			action->resetAction();
		}
	}
	for (Action* action : availableActionsCreateActors)
	{
		action->resetAction();
	}
}

void Manager::ShowStats()
{
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Food : " << std::to_string(world->GetRessourceAmount(RESSOURCE_TYPE::FOOD)) << std::endl;
	std::cout << "Water : " << std::to_string(world->GetRessourceAmount(RESSOURCE_TYPE::WATER)) << std::endl;
	std::cout << "Wood : " << std::to_string(world->GetRessourceAmount(RESSOURCE_TYPE::WOOD)) << std::endl;
	std::cout << "Tree : " << std::to_string(world->GetRessourceAmount(RESSOURCE_TYPE::TREE)) << std::endl;
	std::cout << "House : " << std::to_string(world->GetRessourceAmount(RESSOURCE_TYPE::HOUSE)) << std::endl;
	std::cout << "Villagers : " << std::to_string(world->GetTotalPopulation()) << std::endl;
	std::cout << "---------------------------------" << std::endl;
}
