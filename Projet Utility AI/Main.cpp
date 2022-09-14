#include <iostream>
#include <windows.h>
#include "Manager.h"
#include "World.h"
#include "WorldSettings.h"


int main()
{
	Manager* mainManager = Manager::GetInstance();
	int i = 20;
	while (mainManager->GetWorld()->GetPopulation() < GOAL_MAX_VILLAGER || i > 0) 
	{
		i--;
		mainManager->Update();
		Sleep(1000);
	}

	return 0;
}

