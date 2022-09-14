#pragma once

enum class ACTOR_TYPE
{
	VILLAGER,
	LENGTH,
};

class Actor
{
private:
	float idleTime;
	int foodCost;

public:

	float GetIdleTime() const { return idleTime; };

};

class Villager : public Actor
{

};

