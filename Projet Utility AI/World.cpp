#include <assert.h>
#include "WorldSettings.h"
#include "World.h"
#include "Actor.h"

World::World()
{
	std::vector<Actor*> villagers;
	villagers.reserve(MAX_ACTORS_PER_TYPE);
	for (int i = 0; i < WORLD_START_VILLAGER_AMOUNT; i++)
	{
		villagers.push_back(new Villager());
	}
	actors.emplace(ACTOR_TYPE::VILLAGER, villagers);

	std::vector<Actor*> farmers;
	farmers.reserve(MAX_ACTORS_PER_TYPE);
	for (int i = 0; i < WORLD_START_FARMER_AMOUNT; i++)
	{
		farmers.push_back(new Farmer());
	}
	actors.emplace(ACTOR_TYPE::FARMER, farmers);

	std::vector<Actor*> lumberjacks;
	lumberjacks.reserve(MAX_ACTORS_PER_TYPE);
	for (int i = 0; i < WORLD_START_LUMBERJACK_AMOUNT; i++)
	{
		lumberjacks.push_back(new Lumberjack());
	}
	actors.emplace(ACTOR_TYPE::LUMBERJACK, lumberjacks);

	ressources.reserve((int)RESSOURCE_TYPE::LENGTH);
	ressources.push_back(WORLD_START_FOOD_AMOUNT);
	ressources.push_back(WORLD_START_WATER_AMOUNT);
	ressources.push_back(WORLD_START_WOOD_AMOUNT);
	ressources.push_back(WORLD_START_TREE_AMOUNT);
	ressources.push_back(WORLD_START_HOUSE_AMOUNT);

	maxValueRessources.reserve((int)RESSOURCE_TYPE::LENGTH);
	maxValueRessources.push_back(MAX_FOOD_ALLOWED);
	maxValueRessources.push_back(MAX_WATER_ALLOWED);
	maxValueRessources.push_back(MAX_WOOD_ALLOWED);
	maxValueRessources.push_back(MAX_TREE_ALLOWED);
	maxValueRessources.push_back(GOAL_MAX_VILLAGER);

}

void World::DeInit()
{
	for (int i = 0; i < (int)ACTOR_TYPE::LENGTH; i++)
	{
		for (Actor* actor : actors[(ACTOR_TYPE)i])
		{
			if (actor != nullptr)
			{
				delete actor;
				actor = nullptr;
			}
		}
	}
}

void World::WorldUpdate()
{
	int nbPopDebug = GetTotalPopulation();
	for (int i = 0; i < (int) ACTOR_TYPE::LENGTH; i++)
	{
		auto iterator = actors.find((ACTOR_TYPE)i);
		if(iterator != actors.end())
		{
			for (Actor* actor : iterator->second)
			{
				assert(actor != nullptr);
				actor->UpdateActor(this);
				UpdateRessources(RESSOURCE_TYPE::FOOD, actor->GetFoodCost());
			}
		}
	}
	UpdateRessources(RESSOURCE_TYPE::TREE, NEW_TREE_PER_TICK);
}

void World::UpdateRessources(RESSOURCE_TYPE ressourceType, int amountConsumed)
{
	ressources[(int)ressourceType] += amountConsumed;
	if (ressources[(int)ressourceType] > maxValueRessources[(int)ressourceType])
	{
		ressources[(int)ressourceType] = maxValueRessources[(int)ressourceType];
	}
	else if (ressources[(int)ressourceType] < 0)
	{
		ressources[(int)ressourceType] = 0;
	}
}

void World::KillActor(ACTOR_TYPE actorType, Actor* actor)
{
	auto iterator = actors.find(actorType);
	if (iterator != actors.end())
	{
		for (unsigned int i = 0; i < iterator->second.size(); i++) {
			if (iterator->second[i] == actor)
			{
				auto actorIterator = std::next(iterator->second.begin(), i);
				auto actorIteratorEnd = std::next(iterator->second.begin(), i+1);
				iterator->second.erase(actorIterator, actorIteratorEnd);
			}
		}

	}
}

void World::AddActor(Actor* actor, ACTOR_TYPE actorType)
{
	auto iterator = actors.find(actorType);
	if (iterator != actors.end())
		iterator->second.push_back(actor);
	else
	{
		std::vector<Actor*> newActorType;
		newActorType.resize(MAX_ACTORS_PER_TYPE);
		newActorType.push_back(actor);
		actors[actorType] = newActorType;
	}
}

std::vector<Actor*> World::GetActorsFromType(ACTOR_TYPE actorType) const
{
	auto iterator = actors.find(actorType);
	std::vector<Actor*> actorToEvaluate;
	if (iterator != actors.end())
		return iterator->second;
	return std::vector<Actor*>();
}

Actor* World::HasActorFreeFromType(ACTOR_TYPE actorType)
{
	std::vector<Actor*> villagers = GetActorsFromType(actorType);
	for (Actor* villager : villagers)
	{
		if (!villager->IsWorking())
		{
			return villager;
		}
	}
	return nullptr;
}

int World::GetTotalFoodConsumedPerTick() const
{
	int totalFoodCost = 0;
	for (int i = 0; i < (int)ACTOR_TYPE::LENGTH; i++)
	{
		auto iterator = actors.find((ACTOR_TYPE)i);
		if (iterator != actors.end())
		{
			for (Actor* actor : iterator->second) 
			{
				totalFoodCost += actor->GetFoodCost();
			}
		}
	}
	return totalFoodCost;
}

int World::GetPopulation(ACTOR_TYPE actorType) const
{
	auto iterator = actors.find(actorType);
	if (iterator != actors.end())
	{
		return (int) iterator->second.size();
	}
	return 0;
}

int World::GetTotalPopulation() const
{
	int pop = 0;
	for (int i = 0; i < (int)ACTOR_TYPE::LENGTH; i++)
	{
		pop += GetPopulation((ACTOR_TYPE)i);
	}
	return pop;
}


