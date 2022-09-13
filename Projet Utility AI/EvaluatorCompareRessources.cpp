#include <assert.h>
#include "EvaluatorCompareRessources.h"

EvaluateDivide::EvaluateDivide(RESSOURCE_TYPE ressource)
{
	ressourceType = ressource;
}

float EvaluateDivide::GetScore(const World* world)
{
	assert(world->GetMaxValueRessource((RESSOURCE_TYPE)ressourceType) > 0);
	return world->GetRessourceAmount((RESSOURCE_TYPE)ressourceType) / static_cast<float>(world->GetMaxValueRessource((RESSOURCE_TYPE)ressourceType));
}
