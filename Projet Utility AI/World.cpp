#include <assert.h>
#include "WorldSettings.h"
#include "World.h"
#include "Actor.h"

World::World()
{
	ressources.reserve((int)RESSOURCE_TYPE::LENGTH);
	ressources.push_back(WORLD_START_FOOD_AMOUNT);

	maxValueRessources.reserve((int)RESSOURCE_TYPE::LENGTH);
	maxValueRessources.push_back(MAX_FOOD_ALLOWED);

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

void World::UpdateRessources(RESSOURCE_TYPE ressourceType, int amountConsumed)
{
	ressources[(int)ressourceType] += amountConsumed;
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

int World::GetActorAverageIdleTime(ACTOR_TYPE actorType) const
{
	float idleTime = 0.f;
	std::vector<Actor*> actorWithType = GetActorFromType(actorType);
	if (actorWithType.size() > 0)
	{
		for (int i = 0; i < actorWithType.size(); i++)
		{
			idleTime = actorWithType[i]->GetIdleTime();
		}
	}
	return idleTime / actors.size();
}

std::vector<Actor*> World::GetActorFromType(ACTOR_TYPE actorType) const
{
	auto iterator = actors.find(actorType);
	std::vector<Actor*> actorToEvaluate;
	if (iterator != actors.end())
		return iterator->second;
	return std::vector<Actor*>();
}


