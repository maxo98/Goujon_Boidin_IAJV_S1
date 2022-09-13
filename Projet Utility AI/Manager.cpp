#include "Manager.h"

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

	world = new World();
}

void Manager::DeInit()
{


}

void Manager::Update()
{
	
}

Action* Manager::EvaluateActions()
{
	Action* selectedAction = nullptr;
	float actionValue = 0;
	for (int i = 0; i < availableActions.size(); i++)
	{
		if (!availableActions[i]->CanDoAction(world))
			continue;

		float currentActionValue = availableActions[i]->EvaluateAction(world);
		if (currentActionValue > actionValue)
		{
			actionValue = currentActionValue;
			selectedAction = availableActions[i];
		}
	}
	return selectedAction;
}
