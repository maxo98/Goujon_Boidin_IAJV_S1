#pragma once
#include "Action.h"
#include "WorldSettings.h"

class World;


class Actor
{
protected:
	ACTOR_TYPE actorType;
	bool isWorking;
	int foodCost;
	// type of the task and number of tick to finish it
	ACTION_TYPE currentTaskType;
	int currentTaskDuration; 

public:
	Actor(int foodCost, ACTOR_TYPE type);

	void UpdateActor(World* world);

	void StartTask(ACTION_TYPE actionType, int duration);

	virtual void ExecuteTask(World* world) = 0;

	bool IsWorking() { return isWorking; }

	int GetFoodCost() { return foodCost; }

	ACTION_TYPE GetTaskType() { return currentTaskType; }

	int GetTaskDuration() { return currentTaskDuration; }
};

class Villager : public Actor
{
public:
	Villager();

	void StartTask(ACTION_TYPE actionType, int duration, World* world);

	void ExecuteTask(World* world);
};

class Farmer : public Actor
{
public:
	Farmer();

	void StartTask(ACTION_TYPE actionType, int duration, World* world);

	void ExecuteTask(World* world);
};


class Lumberjack : public Actor
{
public:
	Lumberjack();

	void StartTask(ACTION_TYPE actionType, int duration, World* world);

	void ExecuteTask(World* world);
};
