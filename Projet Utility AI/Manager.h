#pragma once
#include <vector>
#include <map>
#include "WorldSettings.h"

class World;
class Action;

class Manager
{
private:
	static Manager* managerSingleton;
	// actions are separated by the type of actors who can execute them for better handling
	std::map<ACTOR_TYPE,std::vector<Action*>> availableActionsForActors;
	// actions that can't be realised by an actor
	std::vector<Action*> availableActionsCreateActors;
	World* world;

	Manager();

public:

	static Manager* GetInstance();

	void InitManager();

	void DeInit();
	
	void Update();

	int EvaluateActions(std::vector<Action*>* actions);

	void resetActions();

	void ShowStats();

	World* GetWorld() { return world; };
};

