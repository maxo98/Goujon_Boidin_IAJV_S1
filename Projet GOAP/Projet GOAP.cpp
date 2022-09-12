#include <iostream>
#include "AI.h"
#include "Action.h"

int main()
{
	Action a1, a2, a3;

	std::vector<std::pair<Action*, int>> test;

	test.push_back(std::pair<Action*, int>(&a1, 6));
	test.push_back(std::pair<Action*, int>(&a2, 4));
	test.push_back(std::pair<Action*, int>(&a3, 5));

	std::sort(test.begin(), test.end(), sort);

	for (int i = 0; i < test.size(); i++)
	{
		std::cout << test[i].second << std::endl;
	}
}