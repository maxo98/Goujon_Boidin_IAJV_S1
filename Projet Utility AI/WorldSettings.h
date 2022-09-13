#pragma once

//Setup params for the world
constexpr int MAX_ACTORS_PER_TYPE = 50;


constexpr float MAX_EXPECTED_IDLE_TIME = 5.f;

//Setup Max Ressources allowed per type
constexpr int MAX_FOOD_ALLOWED = 100;

//Setup Ressources added or consummed per actions
//create a new villager
constexpr int CREATE_VILLAGER_FOOD_CONSUMPTION = -20;

//produce food
constexpr int PRODUCE_FOOD_AMOUNT_ADDED = 15;