#pragma once
#include <vector>
#include <map>
#include "EvaluatorCompareRessources.h"

class World;
class EvaluatorCompareRessources;

enum class ACTION_TYPE
{
	CREATEVILLAGER,
	PRODUCEFOOD,
	LENGTH
};

class Action
{
protected:
	std::vector<int> ressources;
	std::map<RESSOURCE_TYPE,EvaluatorCompareRessources*> evaluators;

public:
	Action();

	void DeInit();

	virtual bool CanDoAction(World* world) = 0;

	float EvaluateIdleTime(float worldAverageIdleTime);

	virtual float EvaluationRessource(World* world, int ressourceType);

	virtual float EvaluateAction(World* world) = 0;

	virtual void ExecuteAction(World* world) = 0;

	void AddEvaluator(RESSOURCE_TYPE evaluatorType, EvaluatorCompareRessources* evaluator);
};

class CreateVillager : public Action
{
public :
	CreateVillager();

	bool CanDoAction(World* world) override;

	float EvaluateAction(World *world) override;

	void ExecuteAction(World* world) override;
};

class ProduceFood: public Action
{
public:
	ProduceFood();

	bool CanDoAction(World* world) override;

	float EvaluateAction(World* world) override;

	void ExecuteAction(World* world) override;
};

