#pragma once
#include <vector>

class World;
class Action;

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

	int EvaluateActions();

	World* GetWorld() { return world; };
};

