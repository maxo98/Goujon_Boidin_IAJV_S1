#pragma once
#include "World.h"

class EvaluatorCompareRessources
{

public:
	virtual float GetScore(const World* world) = 0;
};

class EvaluateDivide : public EvaluatorCompareRessources
{
private:
	RESSOURCE_TYPE ressourceType;

public:
	EvaluateDivide(RESSOURCE_TYPE ressource);

	float GetScore(const World* world) override;

};

class EvaluateInvExpo : public EvaluatorCompareRessources
{
private:
	RESSOURCE_TYPE ressourceType;

public:
	EvaluateInvExpo(RESSOURCE_TYPE ressource);

	float GetScore(const World* world) override;
};

