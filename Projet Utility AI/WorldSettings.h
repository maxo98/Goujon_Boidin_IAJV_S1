#pragma once

//Here are all the constants necessary to have the world function. 
//it's not properly balanced

// set the speed for the updates of all the classes.
constexpr int TICK_SPEED = 1000;

//Setup Max Villager Goal
constexpr int GOAL_MAX_VILLAGER = 20;

// food consumption at each turn isn't working
constexpr int VILLAGER_FOOD_CONSUMPTION = 0;
constexpr int FARMER_FOOD_CONSUMPTION = 0;
constexpr int LUMBERJACK_FOOD_CONSUMPTION = 0;

//Setup params for the world
constexpr int MAX_ACTORS_PER_TYPE = 50;
constexpr int NEW_TREE_PER_TICK = 2;

//Setup World starting ressources
constexpr int WORLD_START_VILLAGER_AMOUNT = 1;
constexpr int WORLD_START_LUMBERJACK_AMOUNT = 1;
constexpr int WORLD_START_FARMER_AMOUNT = 1;
constexpr int WORLD_START_FOOD_AMOUNT = 50;
constexpr int WORLD_START_WATER_AMOUNT = 50;
constexpr int WORLD_START_WOOD_AMOUNT = 0;
constexpr int WORLD_START_TREE_AMOUNT = 5;
constexpr int WORLD_START_HOUSE_AMOUNT = WORLD_START_VILLAGER_AMOUNT + WORLD_START_LUMBERJACK_AMOUNT + WORLD_START_FARMER_AMOUNT;

//Setup Max Ressources allowed per type
constexpr int MAX_FOOD_ALLOWED = 100;
constexpr int MAX_WATER_ALLOWED = 100;
constexpr int MAX_WOOD_ALLOWED = 100;
constexpr int MAX_TREE_ALLOWED = 20;

//Setup Ressources added or consummed per actions
//create a new villager
constexpr int CREATE_VILLAGER_FOOD_CONSUMPTION = -50;
constexpr int CREATE_FARMER_FOOD_CONSUMPTION = -20;
constexpr int CREATE_LUMBERJACK_FOOD_CONSUMPTION = -30;

//produce food
constexpr int PRODUCE_FOOD_AMOUNT_ADDED = 20;
constexpr int PRODUCE_FOOD_WATER_NEEDED = -20;
constexpr int PRODUCE_FOOD_DURATION = 2;

//build house
constexpr int BUILD_HOUSE_AMOUNT_ADDED = 1;
constexpr int BUILD_HOUSE_WOOD_NEEDED = -40;
constexpr int BUILD_HOUSE_DURATION = 3;

//gather water
constexpr int GATHER_WATER_AMOUNT_ADDED = 30;
constexpr int GATHER_WATER_DURATION = 2;

//chop wood
constexpr int CHOP_WOOD_AMOUNT_ADDED = 20;
constexpr int CHOP_WOOD_TREE_CUT = -2;
constexpr int CHOP_WOOD_DURATION = 2;

enum class RESSOURCE_TYPE
{
	FOOD,
	WATER,
	WOOD,
	TREE,
	HOUSE,
	LENGTH,
};

enum class ACTION_TYPE
{
	CREATEVILLAGER,
	CREATEFARMER,
	CREATELUMBERJACK,
	LENGTHCREATE,
	PRODUCEFOOD,
	BUILDHOUSE,
	GATHERWATER,
	CHOPWOOD,
	LENGTH
};

enum class ACTOR_TYPE
{
	VILLAGER,
	FARMER,
	LUMBERJACK,
	LENGTH,
};