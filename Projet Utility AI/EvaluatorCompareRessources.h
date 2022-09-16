#pragma once
#include "World.h"
#include "WorldSettings.h"

class EvaluatorCompareRessources
{

public:
	virtual float GetScore(const World* world) = 0;
};

class EvaluateDivide : public EvaluatorCompareRessources
{
private:
	RESSOURCE_TYPE ressourceType; 
	float divideParameter;

public:
	EvaluateDivide(RESSOURCE_TYPE ressource, float parameter);

	float GetScore(const World* world) override;
};

class EvaluateInvExpo : public EvaluatorCompareRessources
{
private:
	RESSOURCE_TYPE ressourceType;
	float divider;

public:
	EvaluateInvExpo(RESSOURCE_TYPE ressource, float divider);

	float GetScore(const World* world) override;
};

