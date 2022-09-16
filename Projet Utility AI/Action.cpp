#include <iostream>
#include <string>
#include "WorldSettings.h"
#include "World.h"
#include "Action.h"
#include "Actor.h"
#include "EvaluatorCompareRessources.h"

// Action
Action::Action()
{
	ressources.resize((int)RESSOURCE_TYPE::LENGTH, 0);
	actionDone = false;
}

void Action::DeInit()
{
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		auto iterator = evaluators.find((RESSOURCE_TYPE)i);
		if (iterator != evaluators.end())
		{
			if (iterator->second != nullptr)
			{
				delete iterator->second;
			}
		}
	}
}

float Action::EvaluationRessource(World* world, int ressourceType)
{
	auto iterator = evaluators.find((RESSOURCE_TYPE)ressourceType);
	if (iterator != evaluators.end())
	{
		return iterator->second->GetScore(world);
	}
	return 0.f;
}

float Action::EvaluateAction(World* world)
{
	float value = 0.f;
	int numberEvaluation = 0;
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		if (ressources[i] != 0)
		{
			value += EvaluationRessource(world, i);
			numberEvaluation++;
		}
	}

	return value / numberEvaluation;
}

void Action::AddEvaluator(RESSOURCE_TYPE evaluatorType, EvaluatorCompareRessources* evaluator)
{
	evaluators.emplace(evaluatorType, evaluator);
}


// CreateVillager
CreateVillager::CreateVillager(World* world) : Action()
{
	actorType = ACTOR_TYPE::VILLAGER;

	EvaluateDivide* evaluateDivide = new EvaluateDivide(RESSOURCE_TYPE::FOOD, 1);
	AddEvaluator(RESSOURCE_TYPE::FOOD, evaluateDivide);
	ressources[(int)RESSOURCE_TYPE::FOOD] = CREATE_VILLAGER_FOOD_CONSUMPTION;
}

bool CreateVillager::CanDoAction(World* world)
{
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		int worldRessource = world->GetRessourceAmount((RESSOURCE_TYPE)i);
		int ressourceNeeded = ressources[i];
		if (world->GetRessourceAmount((RESSOURCE_TYPE)i) + ressources[i] + world->GetTotalFoodConsumedPerTick() < 0)
			return false;
	}
	if (world->GetTotalPopulation() >= world->GetRessourceAmount(RESSOURCE_TYPE::HOUSE))
		return false;
	return !actionDone;
}

void CreateVillager::ExecuteAction(World* world)
{
	std::cout << "Creating a new Villager" << std::endl;
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		world->UpdateRessources((RESSOURCE_TYPE)i, ressources[i]);
	}
	world->AddActor(new Villager(), actorType);
	actionDone = true;
}


// Create Farmer
CreateFarmer::CreateFarmer(World* world) : Action()
{
	actorType = ACTOR_TYPE::FARMER;

	EvaluateDivide* evaluateDivide = new EvaluateDivide(RESSOURCE_TYPE::FOOD, (float) world->GetTotalFoodConsumedPerTick());
	AddEvaluator(RESSOURCE_TYPE::FOOD, evaluateDivide);
	ressources[(int)RESSOURCE_TYPE::FOOD] = CREATE_FARMER_FOOD_CONSUMPTION;
}

bool CreateFarmer::CanDoAction(World* world) 
{
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		if (world->GetRessourceAmount((RESSOURCE_TYPE)i) + ressources[i] <= 0)
			return false;
	}
	if (world->GetTotalPopulation() >= world->GetRessourceAmount(RESSOURCE_TYPE::HOUSE))
		return false;
	return !actionDone;
}

void CreateFarmer::ExecuteAction(World* world)
{
	std::cout << "Creating a new Farmer" << std::endl;
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		world->UpdateRessources((RESSOURCE_TYPE)i, ressources[i]);
	}
	world->AddActor(new Villager(), actorType);
	actionDone = true;
}


// Create lumberjack
CreateLumberjack::CreateLumberjack(World* world) : Action()
{
	actorType = ACTOR_TYPE::LUMBERJACK;

	EvaluateDivide* evaluateDivide = new EvaluateDivide(RESSOURCE_TYPE::FOOD, 1);
	AddEvaluator(RESSOURCE_TYPE::FOOD, evaluateDivide);
	ressources[(int)RESSOURCE_TYPE::FOOD] = CREATE_LUMBERJACK_FOOD_CONSUMPTION;
}

bool CreateLumberjack::CanDoAction(World* world)
{
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		if (world->GetRessourceAmount((RESSOURCE_TYPE)i) + ressources[i] < 0)
			return false;
	}
	if (world->GetTotalPopulation() >= world->GetRessourceAmount(RESSOURCE_TYPE::HOUSE))
		return false;
	return !actionDone;
}

void CreateLumberjack::ExecuteAction(World* world)
{
	std::cout << "Creating a new Lumberjack" << std::endl;
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		world->UpdateRessources((RESSOURCE_TYPE)i, ressources[i]);
	}
	world->AddActor(new Villager(), actorType);
	actionDone = true;
}


// ProduceFood
ProduceFood::ProduceFood(World* world) : Action()
{
	EvaluateInvExpo* evaluateInvExpo = new EvaluateInvExpo(RESSOURCE_TYPE::FOOD, (float)world->GetTotalFoodConsumedPerTick());
	AddEvaluator(RESSOURCE_TYPE::FOOD, evaluateInvExpo);
	ressources[(int)RESSOURCE_TYPE::FOOD] = PRODUCE_FOOD_AMOUNT_ADDED;
	ressources[(int)RESSOURCE_TYPE::WATER] = PRODUCE_FOOD_WATER_NEEDED;
}

bool ProduceFood::CanDoAction(World* world)
{
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		if (world->GetRessourceAmount((RESSOURCE_TYPE)i) + ressources[i] < 0)
			return false;
	}
	return world->HasActorFreeFromType(ACTOR_TYPE::FARMER) && !actionDone;
}

void ProduceFood::ExecuteAction(World* world)
{
	Actor* actor = world->HasActorFreeFromType(ACTOR_TYPE::FARMER);
	actor->StartTask(ACTION_TYPE::PRODUCEFOOD, PRODUCE_FOOD_DURATION);
}


//gather water
GatherWater::GatherWater(World* world)
{
	EvaluateInvExpo* evaluateInvExpo = new EvaluateInvExpo(RESSOURCE_TYPE::FOOD, 2);
	AddEvaluator(RESSOURCE_TYPE::FOOD, evaluateInvExpo);
	ressources[(int) RESSOURCE_TYPE::FOOD] = PRODUCE_FOOD_AMOUNT_ADDED;
}

bool GatherWater::CanDoAction(World* world)
{
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		if (world->GetRessourceAmount((RESSOURCE_TYPE)i) + ressources[i] < 0)
			return false;
	}
	return world->HasActorFreeFromType(ACTOR_TYPE::VILLAGER) && !actionDone;
}

void GatherWater::ExecuteAction(World* world)
{
	Actor* actor = world->HasActorFreeFromType(ACTOR_TYPE::VILLAGER);
	actor->StartTask(ACTION_TYPE::GATHERWATER, GATHER_WATER_DURATION);
	actionDone = true;
}


//chop wood
ChopWood::ChopWood(World* world)
{
	EvaluateInvExpo* evaluateInvExpo = new EvaluateInvExpo(RESSOURCE_TYPE::TREE, 2);
	AddEvaluator(RESSOURCE_TYPE::WOOD, evaluateInvExpo);
	ressources[(int) RESSOURCE_TYPE::WOOD] = CHOP_WOOD_AMOUNT_ADDED;
	ressources[(int) RESSOURCE_TYPE::TREE] = CHOP_WOOD_TREE_CUT;
}

bool ChopWood::CanDoAction(World* world)
{
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		if (world->GetRessourceAmount((RESSOURCE_TYPE)i) + ressources[i] < 0)
			return false;
	}
	return world->HasActorFreeFromType(ACTOR_TYPE::LUMBERJACK) && !actionDone;
}

void ChopWood::ExecuteAction(World* world)
{
	Actor* actor = world->HasActorFreeFromType(ACTOR_TYPE::LUMBERJACK);
	actor->StartTask(ACTION_TYPE::CHOPWOOD, CHOP_WOOD_DURATION);
	actionDone = true;
}


// BuildHouse
BuildHouse::BuildHouse(World* world) : Action()
{
	EvaluateInvExpo* evaluateInvExpo = new EvaluateInvExpo(RESSOURCE_TYPE::WOOD, 5);
	AddEvaluator(RESSOURCE_TYPE::WOOD, evaluateInvExpo);
	ressources[(int) RESSOURCE_TYPE::WOOD] = BUILD_HOUSE_WOOD_NEEDED;
}

bool BuildHouse::CanDoAction(World* world)
{
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		if (world->GetRessourceAmount((RESSOURCE_TYPE)i) + ressources[i] < 0)
			return false;
	}
	return world->HasActorFreeFromType(ACTOR_TYPE::VILLAGER) && !actionDone;
}

void BuildHouse::ExecuteAction(World* world)
{
	Actor* actor = world->HasActorFreeFromType(ACTOR_TYPE::VILLAGER);
	actor->StartTask(ACTION_TYPE::BUILDHOUSE, BUILD_HOUSE_DURATION);
	actionDone = true;
}


