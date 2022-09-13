#pragma once
#include "World.h"

class EvaluatorCompareRessources
{

public:
	virtual float GetScore(const World* world) = 0;
};

class EvaluateDivide : EvaluatorCompareRessources
{
private:
	RESSOURCE_TYPE ressourceType;

public:
	EvaluateDivide(RESSOURCE_TYPE ressource);

	float GetScore(const World* world) override;

};

