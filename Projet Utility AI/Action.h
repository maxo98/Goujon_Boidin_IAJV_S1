#pragma once
#include <vector>
#include <map>
#include "WorldSettings.h"

class World;
class EvaluatorCompareRessources;


// Class action and its childs
// check actions, evaluate it and execute
// execution mostly send the order to an actor to execute a task
// except for creating new Actors.

class Action
{
protected:
	// amounts of ressources consummed or gained by doing the action 
	//(can potentially consum or gain multiple type of ressources at once)
	std::vector<int> ressources;
	// to not have an action done twice 
	bool actionDone;
	// for each ressources you can have a different evaluator
	std::map<RESSOURCE_TYPE,EvaluatorCompareRessources*> evaluators;

public:
	Action();

	void DeInit();

	// check if the action is doable
	virtual bool CanDoAction(World* world) = 0;

	// evaluate for a given action the value of the ressource depending criteria using the evaluator specified
	virtual float EvaluationRessource(World* world, int ressourceType);

	// gives a value out of each ressources evaluation
	virtual float EvaluateAction(World* world);

	// either execute the action or give a task to an actor
	virtual void ExecuteAction(World* world) = 0;

	void resetAction() { actionDone = false; };

	// add new evaluator to the action
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

