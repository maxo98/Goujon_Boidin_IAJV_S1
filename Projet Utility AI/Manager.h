#pragma once
#include <vector>
#include "Action.h"
#include "World.h"

class Manager
{
private:
	static Manager* managerSingleton;

	std::vector<Action*> availableActions;
	World* world;

	Manager();

public:

	static Manager* GetInstance();

	void InitManager();

	void DeInit();
	
	void Update();

	Action* EvaluateActions();
};

