#include <assert.h>
#include <iostream>
#include "Actor.h"
#include "WorldSettings.h"
#include "World.h"



Actor::Actor(int foodCost, ACTOR_TYPE type)
{
	isWorking = false;
	this->foodCost = foodCost;
	actorType = type;
	currentTaskDuration = -1;
}

void Actor::UpdateActor(World* world)
{
	if (world->GetRessourceAmount(RESSOURCE_TYPE::FOOD) + foodCost < 0)
	{
		world->KillActor(actorType, this);
		delete this;
	}
	else
	{
		world->UpdateRessources(RESSOURCE_TYPE::FOOD, foodCost);
		if (currentTaskDuration != 0)
		{
			currentTaskDuration--;
		}
		else
		{
			ExecuteTask(world);
		}
	}
}

void Actor::StartTask(ACTION_TYPE actionType, int duration)
{
	currentTaskType= actionType;
	currentTaskDuration = duration;
	isWorking = true;
}

Villager::Villager() : Actor(VILLAGER_FOOD_CONSUMPTION, ACTOR_TYPE::VILLAGER)
{
}

void Villager::StartTask(ACTION_TYPE actionType, int duration, World* world)
{
	Actor::StartTask(actionType, duration);
	if (currentTaskType == ACTION_TYPE::BUILDHOUSE)
		world->UpdateRessources(RESSOURCE_TYPE::WOOD, BUILD_HOUSE_WOOD_NEEDED);
}

void Villager::ExecuteTask(World* world)
{
	if (currentTaskType == ACTION_TYPE::GATHERWATER)
	{
		std::cout << "Gather water " << std::endl;
		world->UpdateRessources(RESSOURCE_TYPE::WATER, GATHER_WATER_AMOUNT_ADDED);
	}
	else if (currentTaskType == ACTION_TYPE::BUILDHOUSE)
	{
		std::cout << "Build house " << std::endl;
		
		world->UpdateRessources(RESSOURCE_TYPE::HOUSE, BUILD_HOUSE_AMOUNT_ADDED);
	}
	isWorking = false;
}

Farmer::Farmer() : Actor(FARMER_FOOD_CONSUMPTION, ACTOR_TYPE::FARMER)
{
}

void Farmer::StartTask(ACTION_TYPE actionType, int duration, World* world)  
{
	Actor::StartTask(actionType, duration);
	world->UpdateRessources(RESSOURCE_TYPE::WATER, PRODUCE_FOOD_WATER_NEEDED);
}

void Farmer::ExecuteTask(World* world)
{
	if (currentTaskType == ACTION_TYPE::PRODUCEFOOD)
	{
		std::cout << "Produce Food " << std::endl;
		world->UpdateRessources(RESSOURCE_TYPE::FOOD, PRODUCE_FOOD_AMOUNT_ADDED);
	}
}


Lumberjack::Lumberjack() : Actor(LUMBERJACK_FOOD_CONSUMPTION, ACTOR_TYPE::LUMBERJACK)
{
}

void Lumberjack::StartTask(ACTION_TYPE actionType, int duration, World* world)
{
	Actor::StartTask(actionType, duration);
	world->UpdateRessources(RESSOURCE_TYPE::TREE, CHOP_WOOD_TREE_CUT);
}

void Lumberjack::ExecuteTask(World* world)
{
	if (currentTaskType == ACTION_TYPE::CHOPWOOD)
	{
		std::cout << "Chop wood " << std::endl;
		world->UpdateRessources(RESSOURCE_TYPE::WOOD, CHOP_WOOD_AMOUNT_ADDED);
		world->UpdateRessources(RESSOURCE_TYPE::TREE, CHOP_WOOD_TREE_CUT);
	}
}
