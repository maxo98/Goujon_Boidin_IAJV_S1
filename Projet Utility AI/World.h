#pragma once
#include <vector>
#include <map>
#include "Actor.h"
#include "WorldSettings.h"

class World
{
private:
	std::map<ACTOR_TYPE, std::vector<Actor*>> actors;
	std::vector<int> maxValueRessources;
	std::vector<int> ressources;

public:
	World();

	void DeInit();

	void WorldUpdate();

	void UpdateRessources(RESSOURCE_TYPE ressourceType, int amountConsumed);

	void KillActor(ACTOR_TYPE actorType, Actor* actor);

	void AddActor(Actor* actor, ACTOR_TYPE actorType);

	int GetRessourceAmount(RESSOURCE_TYPE ressourceType) const { return ressources[(int)ressourceType]; }

	int GetMaxValueRessource(RESSOURCE_TYPE ressourceType) const { return maxValueRessources[(int)ressourceType]; }

	std::vector<Actor*> GetActorsFromType(ACTOR_TYPE actorType) const;

	Actor* HasActorFreeFromType(ACTOR_TYPE actorType);

	int GetTotalFoodConsumedPerTick() const;

	int GetPopulation(ACTOR_TYPE actorType) const;

	int GetTotalPopulation() const;
};

