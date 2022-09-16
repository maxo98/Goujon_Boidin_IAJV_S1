#include <assert.h>
#include <math.h>
#include "EvaluatorCompareRessources.h"


// DIVISION EVAL
EvaluateDivide::EvaluateDivide(RESSOURCE_TYPE ressource, float parameter)
{
	ressourceType = ressource;
	divideParameter = parameter;
}

float EvaluateDivide::GetScore(const World* world)
{
	assert(world->GetRessourceAmount((RESSOURCE_TYPE)ressourceType) > 0);
	float parameter = world->GetRessourceAmount((RESSOURCE_TYPE)ressourceType) - divideParameter;
	if (parameter > world->GetMaxValueRessource((RESSOURCE_TYPE)ressourceType))
	{
		parameter = (float)world->GetMaxValueRessource((RESSOURCE_TYPE)ressourceType);
	}
	int maxVal = world->GetMaxValueRessource((RESSOURCE_TYPE)ressourceType);
	assert(world->GetMaxValueRessource((RESSOURCE_TYPE)ressourceType) != 0);
	return parameter / world->GetMaxValueRessource((RESSOURCE_TYPE)ressourceType);
}


// EXPONENTIAL INVERSE EVAL
EvaluateInvExpo::EvaluateInvExpo(RESSOURCE_TYPE ressource, float divider)
{
	divider = divider == 0 ? 1 : divider;
	ressourceType = ressource;
	this->divider = divider;
	
}

float EvaluateInvExpo::GetScore(const World* world)
{
	
	return (float) (1 / exp(world->GetRessourceAmount((RESSOURCE_TYPE)ressourceType) / (divider * 2)));
}
