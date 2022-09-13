#include <assert.h>
#include "WorldSettings.h"
#include "World.h"

World::World()
{
	ressources.resize((int)RESSOURCE_TYPE::LENGTH, 0);
	maxValueRessources.reserve((int)RESSOURCE_TYPE::LENGTH);

	maxValueRessources.push_back(MAX_FOOD_ALLOWED);

}

void World::UpdateRessources(RESSOURCE_TYPE ressourceType, int amountConsumed)
{
	ressources[(int)ressourceType] += amountConsumed;
}



void World::AddActor(Actor* actor, ACTOR_TYPE actorType)
{
	actors.find(actorType)->second.push_back(actor);
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


