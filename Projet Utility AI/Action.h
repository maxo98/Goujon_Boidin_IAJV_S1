#pragma once
#include "World.h"

enum class ACTION_TYPE
{
	VILLAGER,
	LENGTH
};

class Action
{
protected:
	std::vector<int> ressources;

public:
	Action();

	virtual bool CanDoAction(World* world) = 0;

	float EvaluateIdleTime(float worldAverageIdleTime);

	float EvaluationRessource(World* world, int ressourceType);

	virtual float EvaluateAction(World* world) = 0;

	virtual void ExecuteAction(World* world) = 0;
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

