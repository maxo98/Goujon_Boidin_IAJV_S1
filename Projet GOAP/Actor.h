#pragma once
#include "AI.h"

class Action;

class Actor : public AI
{
private:
	int Ammos;
	int weapons;
	int playerDistance;

public:
	Actor();
};

