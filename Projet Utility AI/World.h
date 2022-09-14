#pragma once
#include <vector>
#include <map>
#include "Actor.h"

class Actor;

enum class RESSOURCE_TYPE
{
	FOOD,
	LENGTH
};

class World
{
private:
	std::map<ACTOR_TYPE, std::vector<Actor*>> actors;
	std::vector<int> maxValueRessources;
	std::vector<int> ressources;

public:
	World();

	void DeInit();

	void UpdateRessources(RESSOURCE_TYPE ressourceType, int amountConsumed);

	void AddActor(Actor* actor, ACTOR_TYPE actorType);

	int GetRessourceAmount(RESSOURCE_TYPE ressourceType) const { return ressources[(int)ressourceType]; }

	int GetMaxValueRessource(RESSOURCE_TYPE ressourceType) const { return maxValueRessources[(int)ressourceType]; }

	int GetActorAverageIdleTime(ACTOR_TYPE actorType) const;

	std::vector<Actor*> GetActorFromType(ACTOR_TYPE actorType) const;

	int GetPopulation() const { return actors.size(); }

};

