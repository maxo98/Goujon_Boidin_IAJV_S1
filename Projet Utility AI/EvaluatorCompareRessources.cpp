#include <assert.h>
#include <math.h>
#include "EvaluatorCompareRessources.h"


// DIVISION EVAL
EvaluateDivide::EvaluateDivide(RESSOURCE_TYPE ressource)
{
	ressourceType = ressource;
}

float EvaluateDivide::GetScore(const World* world)
{
	assert(world->GetRessourceAmount((RESSOURCE_TYPE)ressourceType) > 0);
	return world->GetRessourceAmount((RESSOURCE_TYPE)ressourceType) / static_cast<float>(world->GetMaxValueRessource((RESSOURCE_TYPE)ressourceType));
}


// EXPONENTIAL INVERSE EVAL
EvaluateInvExpo::EvaluateInvExpo(RESSOURCE_TYPE ressource)
{
	ressourceType = ressource;
}

float EvaluateInvExpo::GetScore(const World* world)
{
	assert(world->GetRessourceAmount((RESSOURCE_TYPE)ressourceType) > 0);
	return 1 / exp(world->GetRessourceAmount((RESSOURCE_TYPE)ressourceType) / 4.f);
}
