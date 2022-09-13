#pragma once

enum class ACTOR_TYPE
{
	VILLAGER,
};

class Actor
{
private:
	float idleTime;
	int foodCost;

public:

	float GetIdleTime() { return idleTime; };

};

class Villager : public Actor
{

};

