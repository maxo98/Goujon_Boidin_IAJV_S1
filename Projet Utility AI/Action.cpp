#include <iostream>
#include <string>
#include "WorldSettings.h"
#include "World.h"
#include "Action.h"
#include "Actor.h"




Action::Action()
{
	ressources.reserve((int)RESSOURCE_TYPE::LENGTH);
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
				iterator->second = nullptr;
			}
		}
	}
}

// Action
float Action::EvaluateIdleTime(float worldAverageIdleTime)
{
	return worldAverageIdleTime / MAX_EXPECTED_IDLE_TIME;
}

float Action::EvaluationRessource(World* world, int ressourceType)
{
	auto iterator = evaluators.find((RESSOURCE_TYPE)ressourceType);
	if (iterator != evaluators.end())
	{
		return iterator->second->GetScore(world);
	}
}

void Action::AddEvaluator(RESSOURCE_TYPE evaluatorType, EvaluatorCompareRessources* evaluator)
{
	evaluators.emplace(evaluatorType, evaluator);
}


// CreateVillager
CreateVillager::CreateVillager() : Action()
{
	EvaluateDivide* evaluateDivide = new EvaluateDivide(RESSOURCE_TYPE::FOOD);
	AddEvaluator(RESSOURCE_TYPE::FOOD, evaluateDivide);
	ressources.push_back(CREATE_VILLAGER_FOOD_CONSUMPTION);
}

bool CreateVillager::CanDoAction(World* world)
{
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		if (world->GetRessourceAmount((RESSOURCE_TYPE)i) + ressources[i] <= 0)
			return false;
	}
	return true;
}


float CreateVillager::EvaluateAction(World* world)
{
	float value = 0.f;
	int numberEvaluation = 0;
	for (int i = 0; i < (int) RESSOURCE_TYPE::LENGTH; i++)
	{
		if(ressources[i] != 0)
		{
			value += EvaluationRessource(world, i);
			numberEvaluation++;
		}
	}

	return value / numberEvaluation;
}

void CreateVillager::ExecuteAction(World* world)
{
	std::cout << "Creating a new Villager : " << std::endl;
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		world->UpdateRessources((RESSOURCE_TYPE)i, ressources[i]);
	}
	world->AddActor(new Villager(), ACTOR_TYPE::VILLAGER);
	
}


// ProduceFood
ProduceFood::ProduceFood() : Action()
{
	EvaluateInvExpo* evaluateDivide = new EvaluateInvExpo(RESSOURCE_TYPE::FOOD);
	AddEvaluator(RESSOURCE_TYPE::FOOD, evaluateDivide);
	ressources.push_back(PRODUCE_FOOD_AMOUNT_ADDED);
}

bool ProduceFood::CanDoAction(World* world)
{
	return true;
}

float ProduceFood::EvaluateAction(World* world)
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

void ProduceFood::ExecuteAction(World* world)
{
	std::cout << "Produce food : " << std::to_string(ressources[0]) << " food" << std::endl;
	world->UpdateRessources(RESSOURCE_TYPE::FOOD, ressources[(int)RESSOURCE_TYPE::FOOD]);
}
