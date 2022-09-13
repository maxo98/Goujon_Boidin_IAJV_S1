#include "WorldSettings.h"
#include "Action.h"


Action::Action()
{
	ressources.reserve((int)RESSOURCE_TYPE::LENGTH);
}

// Action
float Action::EvaluateIdleTime(float worldAverageIdleTime)
{
	return worldAverageIdleTime / MAX_EXPECTED_IDLE_TIME;
}

float Action::EvaluationRessource(World* world, int ressourceType)
{
	
}


// CreateVillager
CreateVillager::CreateVillager() : Action()
{
	ressources.push_back(CREATE_VILLAGER_FOOD_CONSUMPTION);
}

bool CreateVillager::CanDoAction(World* world)
{
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		if (ressources[i] > 0)
		{
			if (world->GetRessourceAmount((RESSOURCE_TYPE)i) - ressources[i] >= 0)
				return false;
		}
	}
	return true;
}


float CreateVillager::EvaluateAction(World* world)
{
	float value = 0.f;
	int numberEvaluation = 0;
	for (int i = 0; i < (int) RESSOURCE_TYPE::LENGTH; i++)
	{
		if(ressources[i] > 0)
		{
			value += EvaluationRessource(world, i);
			numberEvaluation++;
		}
	}

	return value / numberEvaluation;
}

void CreateVillager::ExecuteAction(World* world)
{
	for (int i = 0; i < (int)RESSOURCE_TYPE::LENGTH; i++)
	{
		world->UpdateRessources((RESSOURCE_TYPE)i, ressources[i]);
	}
	world->AddActor(new Villager(), ACTOR_TYPE::VILLAGER);
	
}


// ProduceFood
ProduceFood::ProduceFood() : Action()
{
	ressources.push_back(PRODUCE_FOOD_AMOUNT_ADDED);
}

bool ProduceFood::CanDoAction(World* world)
{
	return true;
}

float ProduceFood::EvaluateAction(World* world)
{
	return 0.0f;
}

void ProduceFood::ExecuteAction(World* world)
{
	world->UpdateRessources(RESSOURCE_TYPE::FOOD, ressources[(int)RESSOURCE_TYPE::FOOD]);
}
