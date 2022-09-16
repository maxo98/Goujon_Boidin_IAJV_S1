#pragma once
#include <vector>
#include <map>
#include "WorldSettings.h"

class World;
class EvaluatorCompareRessources;

class Action
{
protected:
	std::vector<int> ressources;
	bool actionDone;
	std::map<RESSOURCE_TYPE,EvaluatorCompareRessources*> evaluators;

public:
	Action();

	void DeInit();

	virtual bool CanDoAction(World* world) = 0;

	virtual float EvaluationRessource(World* world, int ressourceType);

	virtual float EvaluateAction(World* world);

	virtual void ExecuteAction(World* world) = 0;

	void resetAction() { actionDone = false; };

	void AddEvaluator(RESSOURCE_TYPE evaluatorType, EvaluatorCompareRessources* evaluator);

};

class CreateVillager : public Action
{
private:
	ACTOR_TYPE actorType;

public :
	CreateVillager(World* world);

	bool CanDoAction(World* world) override;

	void ExecuteAction(World* world) override;
};

class CreateFarmer : public Action
{
private:
	ACTOR_TYPE actorType;

public:
	CreateFarmer(World* world);

	bool CanDoAction(World* world) override;

	void ExecuteAction(World* world) override;
};

class CreateLumberjack : public Action
{
private:
	ACTOR_TYPE actorType;

public:
	CreateLumberjack(World* world);

	bool CanDoAction(World* world) override;

	void ExecuteAction(World* world) override;
};

class ProduceFood: public Action
{
public:
	ProduceFood(World* world);

	bool CanDoAction(World* world) override;

	void ExecuteAction(World* world) override;
};

class GatherWater : public Action
{
public:
	GatherWater(World* world);

	bool CanDoAction(World* world) override;

	void ExecuteAction(World* world) override;
};

class ChopWood : public Action
{
public:
	ChopWood(World* world);

	bool CanDoAction(World* world) override;

	void ExecuteAction(World* world) override;
};



class BuildHouse : public Action
{
public:
	BuildHouse(World* world);

	bool CanDoAction(World* world) override;

	void ExecuteAction(World* world) override;
};

